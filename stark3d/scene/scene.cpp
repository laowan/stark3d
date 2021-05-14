#include "scene/scene.h"
#include "scene/mesh.h"
#include "scene/camera.h"
#include "utils/fileutils.h"

#define CGLTF_IMPLEMENTATION
#include "external/cgltf/cgltf.h"

SK_BEGIN_NAMESPACE

struct GLTFLoader
{
    std::string gltfPath;
    std::string gltfDir;

    std::string getUriPath(const std::string& uri)
    {
        if (gltfDir.empty())
        {
            GetParentPath(gltfPath, gltfDir);
        }
        std::string ret;
        PathJoin(ret, gltfDir, uri);
        return ret;
    }

    void loadMesh(cgltf_mesh* gltfMesh, cgltf_data* data, Mesh* mesh)
    {
        cgltf_primitive prim = gltfMesh->primitives[0];
        for (int i = 0; i < prim.attributes_count; i++)
        {
            cgltf_attribute attr = prim.attributes[i];
            if (attr.type == cgltf_attribute_type_position ||
                attr.type == cgltf_attribute_type_normal)
            {
                cgltf_accessor* accessor = attr.data;
                if (accessor->type == cgltf_type_vec3)
                {
                    cgltf_size viewOffset = accessor->offset;
                    cgltf_size bufferOffset = accessor->buffer_view->offset;
                    cgltf_buffer* buffer = accessor->buffer_view->buffer;

                    char* bufferData = (char*)buffer->data;
                    float* floatData = (float*)&bufferData[bufferOffset + viewOffset];

                    for (int n = 0; n < accessor->count; n++)
                    {
                        float x = floatData[3 * n];
                        float y = floatData[3 * n + 1];
                        float z = floatData[3 * n + 2];

                        if (attr.type == cgltf_attribute_type_position)
                        {
                            mesh->positions.push_back(Vector3(x, y, z));
                        }
                        else if (attr.type == cgltf_attribute_type_normal)
                        {
                            mesh->normals.push_back(Vector3(x, y, z));
                        }
                    }
                }
            }
        }

        // indices
        {
            cgltf_accessor* accessor = prim.indices;
            if (accessor->component_type == cgltf_component_type_r_16u)
            {
                cgltf_size viewOffset = accessor->offset;
                cgltf_size bufferOffset = accessor->buffer_view->offset;
                cgltf_buffer* buffer = accessor->buffer_view->buffer;

                char* bufferData = (char*)buffer->data;
                uint16* uint16Data = (uint16*)&bufferData[bufferOffset + viewOffset];

                for (int n = 0; n < accessor->count; n++)
                {
                    mesh->indices.push_back(uint16Data[n]);
                }
            }
        }
    }

    void loadNode(cgltf_node* node, cgltf_data* data, Entity* parent, Scene* scene)
    {
        Entity* ent = new Entity(node->name);
        scene->addEntity(ent);

        Transform* trans = ent->getTransform();
        if (parent)
        {
            trans->setParent(parent->getTransform());
        }

        if (node->has_matrix)
        {
            Matrix4 mat(node->matrix);
            trans->setMatrix(mat);
        }

        if (node->mesh)
        {
            Mesh* mesh = new Mesh();
            scene->addMesh(mesh);

            loadMesh(node->mesh, data, mesh);
        }

        for (int i = 0; i < node->children_count; i++)
        {
            loadNode(node->children[i], data, ent, scene);
        }
    }

    bool load(const std::string& path, Scene* scene)
    {
        cgltf_options options;
        memset(&options, 0, sizeof(cgltf_options));

        cgltf_data* data = NULL;
        cgltf_result result = cgltf_parse_file(&options, path.c_str(), &data);
        if (result == cgltf_result_success)
        {
            cgltf_options opt;
            memset(&opt, 0, sizeof(cgltf_options));
            result = cgltf_load_buffers(&opt, data, path.c_str());

            if (result == cgltf_result_success && data->scenes_count > 0)
            {
                cgltf_scene gltfScene = data->scenes[0];
                if (gltfScene.nodes_count > 0)
                {
                    loadNode(gltfScene.nodes[0], data, nullptr, scene);
                }
            }

            cgltf_free(data);
        }
        return false;
    }

    void dump(Entity* ent)
    {

    }
};

Scene::Scene()
{

}

Scene::~Scene()
{

}

Entity* Scene::createEntity(const std::string& name)
{
    Entity* ent = new Entity(name);
    return ent;
}

void Scene::addEntity(Entity* entity)
{
    _entities.push_back(entity);
}

void Scene::removeEntity(Entity* entity)
{
    auto it = std::find(_entities.begin(), _entities.end(), entity);
    if (it != _entities.end())
        _entities.erase(it);
}

bool Scene::loadGLTF(const std::string& path)
{
    GLTFLoader loader;
    return loader.load(path, this);
}

void Scene::update()
{

}

void Scene::render()
{
    _camera->render(this);
}

void Scene::dump()
{
    GLTFLoader loader;
    loader.dump(_entities[0]);
}

SK_END_NAMESPACE
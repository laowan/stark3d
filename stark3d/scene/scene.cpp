#include "scene/scene.h"
#include "scene/mesh.h"
#include "scene/camera.h"
#include "scene/material.h"
#include "scene/meshrenderer.h"
#include "graphics/shader.h"
#include "utils/fileutils.h"

#define CGLTF_IMPLEMENTATION
#include "external/cgltf/cgltf.h"

SK_BEGIN_NAMESPACE

struct GLTFLoader
{
    std::string gltfPath;
    std::string gltfDir;
    Scene* _scene;

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

    void loadMaterial(cgltf_material* gltfMaterial, cgltf_data* data, Material* material)
    {
        Shader* shader = new Shader;
        shader->load("mesh3d");
        shader->compile();
        material->setShader(shader);
    }

    void loadMesh(cgltf_mesh* gltfMesh, cgltf_data* data, Mesh* mesh, Entity* entity)
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

        // material
        Material* material = new Material;
        loadMaterial(prim.material, data, material);

        //Shader* shader = new Shader();
        //shader->load()

        int materialId = _scene->addMaterial(material);
        int meshId = _scene->addMesh(mesh);

        MeshRenderer* meshRender = new MeshRenderer;
        meshRender->setMeshId(meshId);
        meshRender->setMaterialId(materialId);

        _scene->addRenderer(meshRender);
    }

    void loadNode(cgltf_node* node, cgltf_data* data, Entity* parent)
    {
        Entity* ent = new Entity(node->name ? node->name : "default");
        _scene->addEntity(ent);

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
            loadMesh(node->mesh, data, mesh, ent);
        }

        for (int i = 0; i < node->children_count; i++)
        {
            loadNode(node->children[i], data, ent);
        }
    }

    bool load(const std::string& path, Scene* scene)
    {
        _scene = scene;

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
                    loadNode(gltfScene.nodes[0], data, nullptr);
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
    _camera = new Camera;
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

int Scene::addMesh(Mesh* mesh)
{ 
    _meshes.push_back(mesh);
    return _meshes.size(); 
}

Mesh* Scene::getMesh(int n)
{ 
    return _meshes[n - 1];
}

int Scene::addMaterial(Material* material)
{
    _materials.push_back(material);
    return _materials.size();
}

Material* Scene::getMaterial(int n)
{
    return _materials[n - 1];
}

int Scene::addRenderer(Renderer* renderer)
{
    _renderers.push_back(renderer);
    return _renderers.size();
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
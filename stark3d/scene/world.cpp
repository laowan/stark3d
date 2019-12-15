#include "world.h"
#include "mesh.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "utils/shadermanager.h"
#include "utils/renderdevice.h"

#include <map>

SK_BEGIN_NAMESPACE

class WorldImpl : public Impl<World>
{
public:
    WorldImpl();
    ~WorldImpl();

    void renderNode(Camera* camera, const aiScene* scene, const aiNode* node);
    void renderScene(Camera* camera, const aiScene* scene);

    Assimp::Importer importer;
    const aiScene* scene;
    ShaderManager shaderManager;
    RenderDevice renderDevice;

    uint32 fbo = 0;

    std::map<unsigned int, Mesh*> meshes;
};

WorldImpl::WorldImpl()
{

}

WorldImpl::~WorldImpl()
{
    if (fbo)
    {
        renderDevice.destroyRenderBuffer(fbo);
    }
}

void WorldImpl::renderNode(Camera* camera, const aiScene* scene, const aiNode* node)
{
    // take care transform

    // render mesh in this node
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshIdx = node->mMeshes[i];
        if (meshes.find(meshIdx) == meshes.end())
        {
            const aiMesh* mesh = scene->mMeshes[meshIdx];
            Mesh* skMesh = new Mesh(mesh);
            meshes[meshIdx] = skMesh;
        }

        // render this mesh
        Shader* normalShader = shaderManager.getShader("mesh3d");
        meshes[meshIdx]->render(normalShader, &renderDevice);
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        renderNode(camera, scene, node->mChildren[i]);
    }
}

void WorldImpl::renderScene(Camera* camera, const aiScene* scene)
{
    //if (!fbo)
    //{
    //    int winWidth = camera->getViewport().pixWidth;
    //    int winHeight = camera->getViewport().pixHeight;
    //    fbo = renderDevice.createRenderBuffer(winWidth, winHeight);
    //}

    //renderDevice.setRenderBuffer(fbo);

    renderNode(camera, scene, scene->mRootNode);

    //renderDevice.setRenderBuffer(0);
}

World::World()
{
    SK_I(World);
}

World::~World()
{

}

bool World::load(const std::string& path)
{
    SK_D(World);
    d->scene = d->importer.ReadFile(path, 0);
    if (!d->scene)
        return false;

    return true;
}

void World::render(Camera* camera)
{
    SK_D(World);
    if (d->scene)
    {
        d->renderScene(camera, d->scene);
    }
}

SK_END_NAMESPACE
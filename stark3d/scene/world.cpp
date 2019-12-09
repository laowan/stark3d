#include "world.h"
#include "camera.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"

SK_BEGIN_NAMESPACE

class WorldImpl : public Impl<World>
{
public:
    void renderNode(const Camera* camera, const aiScene* scene, const aiNode* node);
    void renderScene(const Camera* camera, const aiScene* scene);

    const aiScene* scene;
    Camera camera;
};

void WorldImpl::renderNode(const Camera* camera, const aiScene* scene, const aiNode* node)
{
    // take care transform
    

    // render mesh in this node
    for (int i = 0; i < node->mNumMeshes; i++)
    {
        unsigned int meshIdx = node->mMeshes[i];
        const aiMesh* mesh = scene->mMeshes[meshIdx];
    }

    for (int i = 0; i < node->mNumChildren; i++)
    {
        renderNode(camera, scene, node->mChildren[i]);
    }
}

void WorldImpl::renderScene(const Camera* camera, const aiScene* scene)
{
    renderNode(camera, scene, scene->mRootNode);
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
    Assimp::Importer imp;
    d->scene = imp.ReadFile(path, 0);
    if (!d->scene)
        return false;

    return true;
}

void World::render()
{
    SK_D(World);
    if (d->scene)
    {
        d->renderScene(&d->camera, d->scene);
    }
}

SK_END_NAMESPACE
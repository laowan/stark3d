#include "world.h"
#include "mesh.h"
#include "font.h"
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

    FontAtlasCache* _fontAtlasCache;
};

WorldImpl::WorldImpl()
{
    _fontAtlasCache = nullptr;
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

        mat4x4 mvpMat;
        mat4x4_identity(mvpMat);

        mat4x4 viewMat;
        camera->getViewMat(viewMat);

        mat4x4 projMat;
        camera->getProjMat(projMat);

        mat4x4_mul(mvpMat, projMat, viewMat);

        // render this mesh
        Shader* normalShader = shaderManager.getShader("mesh3d");
        meshes[meshIdx]->render(normalShader, mvpMat, &renderDevice);
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
    //    int winWidth = camera->getV iewport().pixWidth;
    //    int winHeight = camera->getViewport().pixHeight;
    //    fbo = renderDevice.createRenderBuffer(winWidth, winHeight);
    //}

    //renderDevice.setRenderBuffer(fbo);

    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);

    renderDevice.setClearColor(0.0, 0.0, 0.0, 1.0);
    renderDevice.clearColorBuffer();

    renderNode(camera, scene, scene->mRootNode);

    //renderDevice.setRenderBuffer(0);
}

World::World()
{
    SK_I(World);
}

World::~World()
{
    SK_E(World);
    SK_SAFE_DELETE(d->_fontAtlasCache);
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

FontAtlasCache* World::getFontAtlasCache()
{
    SK_D(World);
    if (d->_fontAtlasCache == nullptr)
    {
        d->_fontAtlasCache = new FontAtlasCache;
    }
    return d->_fontAtlasCache;
}

SK_END_NAMESPACE
#include "resourcemanager.h"
#include "shadermanager.h"
#include "shader.h"
#include "scene/texture.h"
#include <map>

SK_BEGIN_NAMESPACE

class ResourceManagerImpl : public Impl<ResourceManager>
{
public:
    std::map<std::string, Texture*> textures;
    ShaderManager shaderMan;
};

ResourceManager::ResourceManager()
{
    SK_I(ResourceManager);
}

ResourceManager::~ResourceManager()
{
    SK_E(ResourceManager);
}

Shader* ResourceManager::currentShader()
{
    SK_D(ResourceManager);
    return d->shaderMan.currentShader();
}

void ResourceManager::useShader(std::string name)
{
    SK_D(ResourceManager);
    d->shaderMan.use(name);
}

Shader* ResourceManager::loadShader(std::string name)
{
    SK_D(ResourceManager);
    return d->shaderMan.getShader(name);
}

Shader* ResourceManager::getShader(std::string name)
{
    SK_D(ResourceManager);
    return d->shaderMan.getShader(name);
}

Texture* ResourceManager::loadTexture(std::string name)
{
    SK_D(ResourceManager);
    if (d->textures.find(name) == d->textures.end())
    {
        std::string filepath = "./resource/" + name + ".png";
        d->textures[name] = new Texture(filepath);
    }

    return d->textures[name];
}

Texture* ResourceManager::getTexture(std::string name)
{
    SK_D(ResourceManager);
    if (d->textures.find(name) != d->textures.end())
        return d->textures[name];
    else
        return loadTexture(name);
}

SK_END_NAMESPACE


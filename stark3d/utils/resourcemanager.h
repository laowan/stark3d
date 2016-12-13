#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Shader;
class Texture;
class STARK_API ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    Shader* currentShader();
    void useShader(std::string name);
    Shader* loadShader(std::string name);
    Shader* getShader(std::string name);

    Texture* loadTexture(std::string name);
    Texture* getTexture(std::string name);

private:
    SK_DECLARE_IMPL(ResourceManager);
};

SK_END_NAMESPACE

#endif

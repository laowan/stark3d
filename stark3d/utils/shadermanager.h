 #ifndef UTILS_SHADERMANAGER_H
#define UTILS_SHADERMANAGER_H

#include "global.h"
#include "shader.h"

SK_BEGIN_NAMESPACE

class ShaderManager
{
    SK_DECLARE_IMPL(ShaderManager);
public:
    ShaderManager();
    ~ShaderManager();

    void use(std::string name);
    Shader* getShader(std::string name);
    Shader* currentShader();
};

SK_END_NAMESPACE

#endif
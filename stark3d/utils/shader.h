#ifndef UTIL_SHADER_H
#define UTIL_SHADER_H

#include <string>

namespace Util {

class Shader
{
public:
    Shader();
    ~Shader();

    void init(std::string filename);
    void use();
    int program() { return _program; }

private:
    int _program;
};

}

#endif
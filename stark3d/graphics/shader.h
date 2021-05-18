#pragma once

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Program;
class Shader
{
public:

    struct Pass
    {
        std::string vs;
        std::string fs;
        Program* program;

        Pass():program(nullptr) {}
    };

    void load(const std::string& name);

    Program* getProgram() { return _pass.program; }

private:
    Pass _pass;
};

SK_END_NAMESPACE
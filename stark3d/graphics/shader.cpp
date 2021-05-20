#include "graphics/shader.h"
#include "graphics/program.h"
#include "utils/fileutils.h"

SK_BEGIN_NAMESPACE

void Shader::load(const std::string& name)
{
    std::string path;
    PathJoin(path, "../res/shader", name);
    _pass.vs = GetTextFromFile(path + ".vert");
    _pass.fs = GetTextFromFile(path + ".frag");
}

void Shader::compile()
{
    _pass.program = new Program();
    _pass.program->init(_pass.vs, _pass.fs);
}

SK_END_NAMESPACE
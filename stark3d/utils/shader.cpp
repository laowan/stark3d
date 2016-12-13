#include "shader.h"
#include <glload/gl_3_3_comp.h>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

SK_BEGIN_NAMESPACE

GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
{
   GLuint shader = glCreateShader(eShaderType);
   const char *strFileData = strShaderFile.c_str();
   glShaderSource(shader, 1, &strFileData, NULL);

   glCompileShader(shader);

   GLint status;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   {
      GLint infoLogLength;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

      GLchar *strInfoLog = new GLchar[infoLogLength + 1];
      glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

      const char *strShaderType = NULL;
      switch(eShaderType)
      {
      case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
      case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
      case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
      }

      fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
      delete[] strInfoLog;
   }

   return shader;
}

GLuint CreateProgram(const std::vector<GLuint> &shaderList)
{
   GLuint program = glCreateProgram();

   for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
      glAttachShader(program, shaderList[iLoop]);

   glLinkProgram(program);

   GLint status;
   glGetProgramiv (program, GL_LINK_STATUS, &status);
   if (status == GL_FALSE)
   {
      GLint infoLogLength;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

      GLchar *strInfoLog = new GLchar[infoLogLength + 1];
      glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
      fprintf(stderr, "Linker failure: %s\n", strInfoLog);
      delete[] strInfoLog;
   }

   for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
      glDetachShader(program, shaderList[iLoop]);

   return program;
}

ShaderUniforms::ShaderUniforms() :
        mvLoc(0),
        mvpLoc(0),
        colorLoc(0),
        lightPositionLoc(0),
        lightColorLoc(0),
        colorMapLoc(0),
        colorMapLoc2(0),
        filterLoc(0),
        viewportWidthLoc(0),
        viewportHeightLoc(0)
{}

class ShaderImpl : public Impl<Shader>
{
public:
    int _program;
    ShaderUniforms _uniforms;
};


Shader::Shader(std::string filename)
{
    SK_I(Shader);
    d->_program = 0;
    init(filename);
}

Shader::~Shader()
{

}

void Shader::init(std::string filename)
{
    SK_D(Shader);
    vector<string> types;
    types.push_back(".vert");
    types.push_back(".frag");

    vector<GLuint> shaderList;
    for (unsigned int i = 0; i < types.size(); i++)
    {
        string fullpath = "./resource/shader/" + filename + types[i];
        std::ifstream shaderFile(fullpath.c_str());
        std::stringstream shaderData;
        shaderData << shaderFile.rdbuf();
        shaderFile.close();

        GLenum shaderType = 0;
        if (types[i] == ".vert") shaderType = GL_VERTEX_SHADER;
        else if (types[i] == ".frag") shaderType = GL_FRAGMENT_SHADER;

        shaderList.push_back(CreateShader(shaderType, shaderData.str()));
    }

    d->_program = CreateProgram(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

    bind();

}

void Shader::use()
{
    SK_D(Shader);
    glUseProgram(d->_program);
}

int Shader::program()
{
    SK_D(Shader);
    return d->_program; 
}

ShaderUniforms& Shader::uniforms()
{
    SK_D(Shader);
    return d->_uniforms; 
}

void Shader::bind()
{
    SK_D(Shader);
    glBindAttribLocation(d->_program, 0, "aPosition");
    glBindAttribLocation(d->_program, 1, "aNormal");
    glBindAttribLocation(d->_program, 2, "aTexCoord");

    d->_uniforms.mvLoc = glGetUniformLocation(d->_program, "uModelViewMat");
    d->_uniforms.mvpLoc = glGetUniformLocation(d->_program, "uModelViewProjMat");
    d->_uniforms.colorLoc = glGetUniformLocation(d->_program, "uColor");
    d->_uniforms.lightPositionLoc = glGetUniformLocation(d->_program, "uLightPosition");
    d->_uniforms.lightColorLoc = glGetUniformLocation(d->_program, "uLightColor");
    d->_uniforms.colorMapLoc = glGetUniformLocation(d->_program, "uColorMap");
    d->_uniforms.colorMapLoc2 = glGetUniformLocation(d->_program, "uColorMap2");
    d->_uniforms.filterLoc = glGetUniformLocation(d->_program, "uFilterMat");
    d->_uniforms.viewportWidthLoc = glGetUniformLocation(d->_program, "uViewportWidth");
    d->_uniforms.viewportHeightLoc = glGetUniformLocation(d->_program, "uViewportHeight");
}

//! commit the values to the shader
void Shader::commitUniforms()
{
    SK_D(Shader);
    if (d->_uniforms.mvLoc > 0)
        glUniformMatrix4fv(d->_uniforms.mvLoc, 1, GL_FALSE, glm::value_ptr(d->_uniforms.mv));
    if (d->_uniforms.mvpLoc > 0)
        glUniformMatrix4fv(d->_uniforms.mvpLoc, 1, GL_FALSE, glm::value_ptr(d->_uniforms.mvp));
    if (d->_uniforms.colorLoc > 0)
        glUniform4fv(d->_uniforms.colorLoc, 1, glm::value_ptr(d->_uniforms.color));
    if (d->_uniforms.lightPositionLoc > 0)
        glUniform3fv(d->_uniforms.lightPositionLoc, 1, glm::value_ptr(d->_uniforms.lightPosition));
    if (d->_uniforms.lightColorLoc > 0)
        glUniform3fv(d->_uniforms.lightColorLoc, 1, glm::value_ptr(d->_uniforms.lightColor));
    if (d->_uniforms.colorMapLoc > 0)
        glUniform1i(d->_uniforms.colorMapLoc, d->_uniforms.activeTexture);
    if (d->_uniforms.colorMapLoc2 > 0)
        glUniform1i(d->_uniforms.colorMapLoc2, d->_uniforms.activeTexture2);
    if (d->_uniforms.filterLoc > 0)
        glUniformMatrix4fv(d->_uniforms.filterLoc, 1, GL_FALSE, glm::value_ptr(d->_uniforms.filter));
    if (d->_uniforms.viewportWidthLoc > 0)
        glUniform1f(d->_uniforms.viewportWidthLoc, d->_uniforms.viewportWidth);
    if (d->_uniforms.viewportHeightLoc > 0)
        glUniform1f(d->_uniforms.viewportHeightLoc, d->_uniforms.viewportHeight);
}

SK_END_NAMESPACE

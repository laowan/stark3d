#include "shader.h"
#include <glload/gl_3_3.h>

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


Shader::Shader(std::string filename)
{
    _program = 0;
    init(filename);
}

Shader::~Shader()
{

}

void Shader::init(std::string filename)
{
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

    _program = CreateProgram(shaderList);

    std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);

    bind();

}

void Shader::use()
{
    glUseProgram(_program);
}

void Shader::bind()
{
    glBindAttribLocation(_program, 0, "aPosition");
    glBindAttribLocation(_program, 1, "aNormal");
    glBindAttribLocation(_program, 2, "aTexCoord");

    _uniforms.mvLoc = glGetUniformLocation(_program, "uModelViewMat");
    _uniforms.mvpLoc = glGetUniformLocation(_program, "uModelViewProjMat");
    _uniforms.colorLoc = glGetUniformLocation(_program, "uColor");
    _uniforms.lightPositionLoc = glGetUniformLocation(_program, "uLightPosition");
    _uniforms.lightColorLoc = glGetUniformLocation(_program, "uLightColor");
    _uniforms.colorMapLoc = glGetUniformLocation(_program, "uColorMap");
    _uniforms.colorMapLoc2 = glGetUniformLocation(_program, "uColorMap2");
    _uniforms.filterLoc = glGetUniformLocation(_program, "uFilterMat");
    _uniforms.viewportWidthLoc = glGetUniformLocation(_program, "uViewportWidth");
    _uniforms.viewportHeightLoc = glGetUniformLocation(_program, "uViewportHeight");
}

//! commit the values to the shader
void Shader::commitUniforms()
{
    if (_uniforms.mvLoc > 0)
        glUniformMatrix4fv(_uniforms.mvLoc, 1, GL_FALSE, glm::value_ptr(_uniforms.mv));
    if (_uniforms.mvpLoc > 0)
        glUniformMatrix4fv(_uniforms.mvpLoc, 1, GL_FALSE, glm::value_ptr(_uniforms.mvp));
    if (_uniforms.colorLoc > 0)
        glUniform4fv(_uniforms.colorLoc, 1, glm::value_ptr(_uniforms.color));
    if (_uniforms.lightPositionLoc > 0)
        glUniform3fv(_uniforms.lightPositionLoc, 1, glm::value_ptr(_uniforms.lightPosition));
    if (_uniforms.lightColorLoc > 0)
        glUniform3fv(_uniforms.lightColorLoc, 1, glm::value_ptr(_uniforms.lightColor));
    if (_uniforms.colorMapLoc > 0)
        glUniform1i(_uniforms.colorMapLoc, _uniforms.activeTexture);
    if (_uniforms.colorMapLoc2 > 0)
        glUniform1i(_uniforms.colorMapLoc2, _uniforms.activeTexture2);
    if (_uniforms.filterLoc > 0)
        glUniformMatrix4fv(_uniforms.filterLoc, 1, GL_FALSE, glm::value_ptr(_uniforms.filter));
    if (_uniforms.viewportWidthLoc > 0)
        glUniform1f(_uniforms.viewportWidthLoc, _uniforms.viewportWidth);
    if (_uniforms.viewportHeightLoc > 0)
        glUniform1f(_uniforms.viewportHeightLoc, _uniforms.viewportHeight);
}

SK_END_NAMESPACE

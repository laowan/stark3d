#include "shader.h"
#include <glload/gl_3_3.h>

#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

namespace Util {

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

        cout << shaderData.str() << endl;

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
    glBindAttribLocation(_program, 0, "position");
    glBindAttribLocation(_program, 1, "normal");

    _uniforms.mvpUniform = glGetUniformLocation(_program, "uModelViewProjMat");
    _uniforms.color = glGetUniformLocation(_program, "uColor");
    _uniforms.lightPosition = glGetUniformLocation(_program, "uLightPosition");
    _uniforms.lightColor = glGetUniformLocation(_program, "uLightColor");

}

}

#pragma once

#include "utils/gldefine.h"
#include "global.h"
#include <string>
#include <map>

SK_BEGIN_NAMESPACE

class Program
{
public:
    Program() : _id(0) {}

    bool initFromFile(const std::string& vs, const std::string& fs);

    void use();
    int getHandle(const std::string& name, bool errorNotExist = true);
    void setUniform1i(const std::string& name, GLint x);
    void setUniform2i(const std::string& name, GLint x, GLint y);
    void setUniform1iv(const std::string& name, int count, GLint* p);
    void setUniform1f(const std::string& name, GLfloat x);
    void setUniform2f(const std::string& name, GLfloat x, GLfloat y);
    void setUniform3f(const std::string& name, GLfloat x, GLfloat y, GLfloat z);
    void setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setUniform1fv(const std::string& name, int count, GLfloat* p);
    void setUniform2fv(const std::string& name, int count, GLfloat* p);
    void setUniform4fv(const std::string& name, int count, GLfloat* p);
    void setUniformMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value);
    void setUniformMatrix3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value);
    void setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* ptr);
    void setVertexAttrib(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, int offset);
    void disableVertexAttrib(const std::string& name);
    void setVertexAttribDivisor(const std::string& name, GLuint divisor);
    void setUniformTexture(const std::string& name, GLint x, GLuint textureID, GLenum target = GL_TEXTURE_2D);
    //void setTexture(const std::string& name, GLint x, OF_Texture* texture);
    void drawElements(GLenum mode, GLsizei count, GLenum type, GLint first);
    void drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLint first, GLsizei primcount);
    void drawArrays(GLenum mode, GLint first, GLsizei count);
    void drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount);

    int  getUniformCount();
    //void getUniformInfo(int nIndex, SUniformInfo& rInfo);

private:
    int _id;
    std::map<std::string, int> _shaderHandleMap;
};

SK_END_NAMESPACE
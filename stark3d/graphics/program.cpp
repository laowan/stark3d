#include "graphics/program.h"

SK_BEGIN_NAMESPACE

bool Program::initFromFile(const std::string& vs, const std::string& fs)
{
    return true;
}

void Program::use()
{
    glUseProgram(_id);
}

int Program::getHandle(const std::string& name, bool errorNotExist)
{
    std::map<std::string, int>::const_iterator it = _shaderHandleMap.find(name);
    if (it != _shaderHandleMap.end())
    {
        return it->second;
    }

    int handle = glGetAttribLocation(_id, name.c_str());
    if (handle == -1)
    {
        handle = glGetUniformLocation(_id, name.c_str());
    }

    if (handle == -1 && errorNotExist)
    {
        printf("Could not get attrib location for %s", name.c_str());
    }
    else
    {
        _shaderHandleMap.insert(std::map<std::string, int>::value_type(name, handle));
    }
    return handle;
}

void Program::setUniform1i(const std::string& name, GLint x)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform1i(location, x);
    }
}

void Program::setUniform2i(const std::string& name, GLint x, GLint y)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform2i(location, x, y);
    }
}

void Program::setUniform1iv(const std::string& name, int count, GLint* p)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform1iv(location, count, p);
    }
}

void Program::setUniform1f(const std::string& name, GLfloat x)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform1f(location, x);
    }
}

void Program::setUniform2f(const std::string& name, GLfloat x, GLfloat y)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform2f(location, x, y);
    }
}

void Program::setUniform3f(const std::string& name, GLfloat x, GLfloat y, GLfloat z)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform3f(location, x, y, z);
    }
}

void Program::setUniform4f(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform4f(location, x, y, z, w);
    }
}

void Program::setUniform1fv(const std::string& name, int count, GLfloat* p)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform1fv(location, count, p);
    }
}

void Program::setUniform2fv(const std::string& name, int count, GLfloat* p)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform2fv(location, count, p);
    }
}

void Program::setUniform4fv(const std::string& name, int count, GLfloat* p)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniform4fv(location, count, p);
    }
}

void Program::setUniformMatrix4fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniformMatrix4fv(location, count, transpose, value);
    }
}

void Program::setUniformMatrix3fv(const std::string& name, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    GLint location = getHandle(name);
    if (-1 != location)
    {
        glUniformMatrix3fv(location, count, transpose, value);
    }
}

void Program::setVertexAttribPointer(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, void* ptr)
{
    GLint index = getHandle(name);
    if (-1 != index)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, size, type, normalized, stride, ptr);
    }
}

void Program::setVertexAttrib(const std::string& name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, int offset)
{
    setVertexAttribPointer(name, size, type, normalized, stride, (void*)(intptr_t)offset);
}

void Program::disableVertexAttrib(const std::string& name)
{
    GLint index = getHandle(name);
    if (-1 != index)
    {
        glDisableVertexAttribArray(index);
    }
}

void Program::setVertexAttribDivisor(const std::string& name, GLuint divisor)
{
    GLint index = getHandle(name);
    if (-1 != index)
    {
        glEnableVertexAttribArray(index);
        if (glVertexAttribDivisor)
        {
            glVertexAttribDivisor(index, divisor);
        }
    }
}

void Program::setUniformTexture(const std::string& name, GLint x, GLuint textureID, GLenum target /*= GL_TEXTURE_2D*/)
{
    int location = getHandle(name);
    if (-1 != location)
    {
        glUniform1i(location, x);
        glActiveTexture(GL_TEXTURE0 + x);
        glBindTexture(target, textureID);
    }
}

/*
void Program::setTexture(const std::string& name, GLint x, OF_Texture* texture)
{
    OF_D(Program);
    int location = getHandle(name);
    if (-1 != location)
    {
        glUniform1i(location, x);
        glActiveTexture(GL_TEXTURE0 + x);
        glBindTexture(texture->target, texture->textureID);
    }

    if (texture->textureID_a)
    {
        std::string strA = name;
        if (strA[strA.length() - 1] >= '0' && strA[strA.length() - 1] <= '9')
        {
            strA.insert(strA.length() - 1, "_a");
            strA[strA.length() - 1] = strA[strA.length() - 1] + 1;
        }
        else
        {
            strA += "_a";
        }

        int location = getHandle(strA);
        if (-1 != location)
        {
            glUniform1i(location, x + 1);
            glActiveTexture(GL_TEXTURE0 + x + 1);
            glBindTexture(texture->target, texture->textureID_a);
        }
    }
}
*/
void Program::drawElements(GLenum mode, GLsizei count, GLenum type, GLint first)
{
#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glEnable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    }
#endif

    glDrawElements(mode, count, type, (const void*)(intptr_t)first);

#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glDisable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glDisable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    }
#endif
}

void Program::drawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLint first, GLsizei primcount)
{
#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glEnable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    }
#endif

    if (glDrawElementsInstanced)
    {
        glDrawElementsInstanced(mode, count, type, (const void*)(intptr_t)first, primcount);
    }

#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glDisable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glDisable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    }
#endif
}

void Program::drawArrays(GLenum mode, GLint first, GLsizei count)
{
#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glEnable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    }
#endif

    glDrawArrays(mode, first, count);

#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glDisable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glDisable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    }
#endif
}

void Program::drawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glEnable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
    }
#endif

    if (glDrawArraysInstanced)
    {
        glDrawArraysInstanced(mode, first, count, primcount);
    }

#ifdef GL_PROGRAM_POINT_SIZE
    if (mode == GL_POINTS)
    {
        glDisable(GL_PROGRAM_POINT_SIZE);
#if defined(OF_WIN32) || defined(_WIN32) || defined(WIN32)
        glDisable(GL_POINT_SPRITE);
#endif
        glPointParameterf(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
    }
#endif
}

int Program::getUniformCount()
{
    GLint nCount;
    glGetProgramiv(_id, GL_ACTIVE_UNIFORMS, &nCount);
    return nCount;
}

SK_END_NAMESPACE
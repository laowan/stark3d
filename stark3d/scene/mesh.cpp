#include "mesh.h"
#include "utils/gldefine.h"

SK_BEGIN_NAMESPACE

Mesh::Mesh() : _vbo(0), _ibo(0)
{
    
}

Mesh::~Mesh()
{
    
}

int Mesh::getVBO()
{
    if (_vbo == 0)
    {
        glGenBuffers(1, (GLuint*)&_vbo);
    }

    int vertexCount = (int)positions.size();
    int bufferSize = 0;

    if (positions.size() > 0) bufferSize += sizeof(Vector3) * vertexCount;
    if (normals.size() > 0) bufferSize += sizeof(Vector3) * vertexCount;
    if (tangents.size() > 0) bufferSize += sizeof(Vector3) * vertexCount;
    if (uv.size() > 0) bufferSize += sizeof(Vector2) * vertexCount;

    char* buffer = (char*)malloc(bufferSize);
    int offset = 0;

    if (positions.size() > 0)
    {
        int size = sizeof(Vector3) * vertexCount;
        memcpy(&buffer[offset], positions.data(), size);
        offset += size;
    }
    if (normals.size() > 0)
    {
        int size = sizeof(Vector3) * vertexCount;
        memcpy(&buffer[offset], normals.data(), size);
        offset += size;
    }
    if (tangents.size() > 0)
    {
        int size = sizeof(Vector3) * vertexCount;
        memcpy(&buffer[offset], tangents.data(), size);
        offset += size;
    }
    if (uv.size() > 0)
    {
        int size = sizeof(Vector2) * vertexCount;
        memcpy(&buffer[offset], uv.data(), size);
        offset += size;
    }

    glBindBuffer(GL_ARRAY_BUFFER, (GLuint)_vbo);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);

    free(buffer);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return _vbo;
}

int Mesh::getIBO()
{
    if (_ibo == 0)
    {
        glGenBuffers(1, (GLuint*)&_ibo);

        int indexCount = (int)indices.size();
        int bufferSize = sizeof(uint16) * indexCount;
        char* buffer = (char*)malloc(bufferSize);

        memcpy(buffer, &indices[0], bufferSize);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);

        free(buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    return _ibo;
}

SK_END_NAMESPACE

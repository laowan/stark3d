#include "bsp.h"
#include "module.h"

SK_BEGIN_NAMESPACE

BSP::BSP() : _numVertices(0), _vertices(NULL),
             _numPolygonFaces(0), _polygonFaces(NULL),
             _numPatches(0), _patches(NULL),
             _numMeshFaces(0)
{

}

BSP::~BSP()
{

}

bool BSP::load(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        return false;
    }

    fread(&_header, sizeof(BSP_HEADER), 1, file);

    if (_header.string[0] != 'I' || _header.string[1] != 'B' ||
        _header.string[2] != 'S' || _header.string[3] != 'P' ||
        _header.version != 0x2E)
    {
        return false;
    }

    if (!loadVertices(file))
        return false;

    if (!loadFaces(file))
        return false;

    if (!loadBSPData(file))
        return false;

    fclose(file);
    return true;
}

bool BSP::loadVertices(FILE* file)
{
    // calculate number of vertices
    _numVertices = _header.directoryEntries[bspVertices].length/sizeof(BSP_LOAD_VERTEX);

    BSP_LOAD_VERTEX* ldVertices = new BSP_LOAD_VERTEX[_numVertices];
    if (!ldVertices)
        return false;

    fseek(file, _header.directoryEntries[bspVertices].offset, SEEK_SET);
    fread(ldVertices, _header.directoryEntries[bspVertices].length, 1, file);

    _vertices = new BSP_VERTEX[_numVertices];
    if (!_vertices)
        return false;

    for (int i = 0; i < _numVertices; i++)
    {
        // swap y and z and negate z
        _vertices[i].position.x = ldVertices[i].position.x;
        _vertices[i].position.y = ldVertices[i].position.z;
        _vertices[i].position.z =-ldVertices[i].position.y;

        // scale down
        _vertices[i].position /= 64;

        // transfer texture coordinates (invert t)
        _vertices[i].decalS = ldVertices[i].decalS;
        _vertices[i].decalT = -ldVertices[i].decalT;

        // transfer lightmap coordinates
        _vertices[i].lightmapS = ldVertices[i].lightmapS;
        _vertices[i].lightmapT = ldVertices[i].lightmapT;
    }

    if (ldVertices)
        delete[] ldVertices;
    ldVertices = NULL;

    std::vector<float> data;
    data.reserve(3*_numVertices);
    for (int i = 0; i < _numVertices; i++)
    {
        data.push_back(_vertices[i].position.x);
        data.push_back(_vertices[i].position.y);
        data.push_back(_vertices[i].position.z);
    }

    glGenBuffers(1, (GLuint*)&_vb);
    glBindBuffer(GL_ARRAY_BUFFER, _vb);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), (void*)&data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

bool BSP::loadFaces(FILE* file)
{
    _numTotalFaces = _header.directoryEntries[bspFaces].length/sizeof(BSP_LOAD_FACE);

    BSP_LOAD_FACE* ldFaces = new BSP_LOAD_FACE[_numTotalFaces];
    if (!ldFaces)
        return false;

    fseek(file, _header.directoryEntries[bspFaces].offset, SEEK_SET);
    fread(ldFaces, _header.directoryEntries[bspFaces].length, 1, file);

    _faceDirectory = new BSP_FACE_DIRECTORY_ENTRY[_numTotalFaces];
    if (!_faceDirectory)
        return false;

    memset(_faceDirectory, 0, _numTotalFaces*sizeof(BSP_FACE_DIRECTORY_ENTRY));

    for (int i = 0; i < _numTotalFaces; i++)
    {
        if (ldFaces[i].type == bspPolygonFace)
            _numPolygonFaces++;
        if (ldFaces[i].type == bspPatch)
            _numPatches++;
        if (ldFaces[i].type == bspMeshFace)
            _numMeshFaces++;
    }

    // create space for BSP_POLYGON_FACE
    _polygonFaces = new BSP_POLYGON_FACE[_numPolygonFaces];
    if (!_polygonFaces)
        return false;

    int currentFace = 0;
    for (int i = 0; i < _numTotalFaces; i++)
    {
        if (ldFaces[i].type != bspPolygonFace)
            continue;

        _polygonFaces[currentFace].firstVertexIndex = ldFaces[i].firstVertexIndex;
        _polygonFaces[currentFace].numVertices = ldFaces[i].numVertices;
        _polygonFaces[currentFace].textureIndex = ldFaces[i].texture;
        _polygonFaces[currentFace].lightmapIndex = ldFaces[i].lightmapIndex;

        _faceDirectory[i].faceType = bspPolygonFace;
        _faceDirectory[i].typeFaceNumber = currentFace;

        currentFace++;
    }

    // create space for BSP_MESH_FACE
    _meshFaces = new BSP_MESH_FACE[_numMeshFaces];
    if (!_meshFaces)
        return false;

    currentFace = 0;
    for (int i = 0; i < _numTotalFaces; i++)
    {
        if (ldFaces[i].type != bspMeshFace)
            continue;

        _meshFaces[currentFace].firstVertexIndex = ldFaces[i].firstVertexIndex;
        _meshFaces[currentFace].numVertices = ldFaces[i].numVertices;
        _meshFaces[currentFace].textureIndex = ldFaces[i].texture;
        _meshFaces[currentFace].lightmapIndex = ldFaces[i].lightmapIndex;
        _meshFaces[currentFace].firstMeshIndex = ldFaces[i].firstMeshIndex;
        _meshFaces[currentFace].numMeshIndices = ldFaces[i].numMeshIndices;

        _faceDirectory[i].faceType = bspMeshFace;
        _faceDirectory[i].typeFaceNumber = currentFace;

        currentFace++;
    }

    // create space for BSP_PATCH

    return true;
}

bool BSP::loadBSPData(FILE* file)
{
    return true;
}

bool BSP::render(RenderAction* act)
{
    Shader* shader = Module::shaderMan().currentShader();
    ShaderUniforms& uniforms = shader->uniforms();
    uniforms.mvp *= act->_modelMat.glMatrix();
    uniforms.color = act->_color;
    shader->commitUniforms();

    glBindBuffer(GL_ARRAY_BUFFER, _vb);

    glEnableVertexAttribArray(0);

    int stride(sizeof(float)* 3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

    glDrawArrays(GL_LINES, 0, _numVertices);

    glDisableVertexAttribArray(0);

    return true;
}

SK_END_NAMESPACE

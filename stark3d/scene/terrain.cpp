#include "terrain.h"
#include <glload/gl_3_3.h>
#include <fstream>

SK_BEGIN_NAMESPACE

Terrain::Terrain(std::string heightmapFileName,
                 int numVertsPerRow,
                 int numVertsPerCol,
                 int cellSpacing,    // space between cells
                 float heightScale)
{
    _vb = 0;
    _ib = 0;

    _numVertsPerRow = numVertsPerRow;
    _numVertsPerCol = numVertsPerCol;
    _cellSpacing = cellSpacing;
    _heightScale = heightScale;

    _numCellsPerRow = numVertsPerRow - 1;
    _numCellsPerCol = numVertsPerCol - 1;
    
    _width = _numCellsPerRow * cellSpacing;
    _depth = _numCellsPerCol * cellSpacing;

    _numVertices = numVertsPerRow * numVertsPerCol;
    _numTriangles = _numCellsPerRow * _numCellsPerCol * 2;

    if (!readRawFile(heightmapFileName))
        return;

    for (size_t i = 0; i < _heightmap.size(); i++)
        _heightmap[i] *= heightScale;

    if (!computeVertices())
        return;

    if (!computeIndices())
        return;
}

Terrain::~Terrain()
{
    if (_vb) { glDeleteBuffers(1, (GLuint*)&_vb); _vb = 0; }
    if (_ib) { glDeleteBuffers(1, (GLuint*)&_ib); _ib = 0; }
}

int Terrain::getHeightmapEntry(int row, int col)
{
    return 1;
}

void Terrain::setHeightmapEntry(int row, int col, int value)
{}

float Terrain::getHeight(float x, float z)
{
    return 1.0;
}

bool Terrain::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vb);

    glEnableVertexAttribArray(0);

    int stride(sizeof(float)* 3 + sizeof(float)* 2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ib);

    glDrawElements(GL_TRIANGLES, _numTriangles*3, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

bool Terrain::readRawFile(std::string fileName)
{
    std::vector<unsigned char> in(_numVertices);
    std::ifstream inFile(fileName.c_str(), std::ios_base::binary);
    if (!inFile.is_open())
        return false;

    inFile.read((char*)&in[0], in.size());
    inFile.close();

    // copy char vector to int vector
    _heightmap.resize(_numVertices);

    for (size_t i = 0; i < in.size(); i++)
        _heightmap[i] = in[i];

    return true;
}

bool Terrain::computeVertices()
{
    std::vector<TerrainVertex> vts;
    for (int i = 0; i < _numVertsPerCol; i++)
    {
        for (int j = 0; j < _numVertsPerRow; j++)
        {
            int idx = i*_numVertsPerRow + j;
            
            float x = -_width/2 + _cellSpacing*j;
            float y = _heightmap[idx];
            float z = -_depth/2 + _cellSpacing*i;

            vts.push_back(TerrainVertex(
                    x, y, z,
                    (float)j/_numCellsPerRow,
                    (float)i/_numCellsPerCol
                ));

            _boundingBox.add(x, y, z);
        }
    }

    glGenBuffers(1, (GLuint*)&_vb);
    glBindBuffer(GL_ARRAY_BUFFER, _vb);
    
    int sz = sizeof(TerrainVertex);
    glBufferData(GL_ARRAY_BUFFER, vts.size()*sizeof(TerrainVertex),
                (void*)&vts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

bool Terrain::computeIndices()
{
    std::vector<int> idx;
    for (int i = 0; i < _numCellsPerCol; i++)
    {
        for (int j = 0; j < _numCellsPerRow; j++)
        {
            idx.push_back(i*(_numCellsPerRow + 1) + j);
            idx.push_back((i+1)*(_numCellsPerRow + 1) + j);
            idx.push_back(i*(_numCellsPerRow + 1) + j + 1);
            
            idx.push_back(i*(_numCellsPerRow + 1) + j + 1);
            idx.push_back((i + 1)*(_numCellsPerRow + 1) + j);
            idx.push_back((i + 1)*(_numCellsPerRow + 1) + j + 1);
        }
    }

    glGenBuffers(1, (GLuint*)&_ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size()*sizeof(GLint),
                (void*)&idx[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return true;
}

SK_END_NAMESPACE

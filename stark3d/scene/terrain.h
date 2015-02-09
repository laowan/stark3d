#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <vector>
#include <string>

#include "node.h"

SK_BEGIN_NAMESPACE

class Terrain : public SceneNode
{
    struct TerrainVertex
    {
        TerrainVertex(float x, float y, float z, float u, float v)
        {
            _x = x; _y = y; _z = z; _u = u; _v = v;
        }
        float _x, _y, _z;
        float _u, _v;
    };

public:
    Terrain(
        std::string heightmapFileName,
        int numVertsPerRow,
        int numVertsPerCol,
        int cellSpacing,    // space between cells
        float heightScale);

    ~Terrain();

    int  getHeightmapEntry(int row, int col);
    void setHeightmapEntry(int row, int col, int value);

    float getHeight(float x, float z);

    bool render();

private:
    bool readRawFile(std::string fileName);
    bool  computeVertices();
    bool  computeIndices();

    int _vb; // vertex buffer
    int _ib; // index buffer

    int _numVertsPerRow;
    int _numVertsPerCol;
    int _cellSpacing;

    int _numCellsPerRow;
    int _numCellsPerCol;
    int _width;
    int _depth;
    int _numVertices;
    int _numTriangles;

    float _heightScale;
    std::vector<int> _heightmap;

    
};
SK_END_NAMESPACE

#endif
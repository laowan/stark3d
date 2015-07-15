#ifndef SCENE_BSP_H
#define SCENE_BSP_H

#include "global.h"
#include "renderaction.h"
#include "node.h"

SK_BEGIN_NAMESPACE

// Some codes are from below link. See for more details.
// http://www.paulsprojects.net/opengl/q3bsp/q3bsp.html

//Directory entry in header
class BSP_DIRECTORY_ENTRY
{
public:
    int offset;
    int length;
};

//Types of directory entry
enum BSP_DIRECTORY_ENTRY_TYPE
{
    bspEntities = 0,
    bspTextures,
    bspPlanes,
    bspNodes,
    bspLeaves,
    bspLeafFaces,
    bspLeafBrushes,
    bspModels,
    bspBrushes,
    bspBrushSides,
    bspVertices,
    bspMeshIndices,
    bspEffect,
    bspFaces,
    bspLightmaps,
    bspLightVols,
    bspVisData
};

//BSP file header
class BSP_HEADER
{
public:
    char string[4];
    int version;
    BSP_DIRECTORY_ENTRY directoryEntries[17];
};

//vertex as found in file
class BSP_LOAD_VERTEX
{
public:
    glm::vec3 position;
    float decalS, decalT;
    float lightmapS, lightmapT;
    glm::vec3 normal;
    GLubyte color[4];
};

//vertex as used for drawing
class BSP_VERTEX
{
public:
    glm::vec3 position;
    float decalS, decalT;
    float lightmapS, lightmapT;

    BSP_VERTEX operator+(const BSP_VERTEX & rhs) const
    {
        BSP_VERTEX result;
        result.position = position + rhs.position;
        result.decalS = decalS + rhs.decalS;
        result.decalT = decalT + rhs.decalT;
        result.lightmapS = lightmapS + rhs.lightmapS;
        result.lightmapT = lightmapT + rhs.lightmapT;

        return result;
    }

    BSP_VERTEX operator*(const float rhs) const
    {
        BSP_VERTEX result;
        result.position = position*rhs;
        result.decalS = decalS*rhs;
        result.decalT = decalT*rhs;
        result.lightmapS = lightmapS*rhs;
        result.lightmapT = lightmapT*rhs;

        return result;
    }
};


//types of faces
enum BSP_FACE_TYPE
{
    bspPolygonFace = 1,
    bspPatch,
    bspMeshFace,
    bspBillboard
};

//Stores which type each face is.
//for example, stores face 8 is a polygon face. It is polygonFace[3]
class BSP_FACE_DIRECTORY_ENTRY
{
public:
    BSP_FACE_TYPE faceType;
    int typeFaceNumber;		//face number in the list of faces of this type
};

//face as found in the file
class BSP_LOAD_FACE
{
public:
    int texture;
    int effect;
    int type;
    int firstVertexIndex;
    int numVertices;
    int firstMeshIndex;
    int numMeshIndices;
    int lightmapIndex;
    int lightmapStart[2];
    int lightmapSize[2];
    glm::vec3 lightmapOrigin;
    glm::vec3 sTangent, tTangent;
    glm::vec3 normal;
    int patchSize[2];
};

//polygon face for drawing
class BSP_POLYGON_FACE
{
public:
    int firstVertexIndex;
    int numVertices;
    int textureIndex;
    int lightmapIndex;
};

//mesh face for drawing
class BSP_MESH_FACE
{
public:
    int firstVertexIndex;
    int numVertices;
    int textureIndex;
    int lightmapIndex;
    int firstMeshIndex;
    int numMeshIndices;
};

//every patch (curved surface) is split into biquadratic (3x3) patches
class BSP_BIQUADRATIC_PATCH
{
public:
    bool Tesselate(int newTesselation);
    void Draw();

    BSP_VERTEX controlPoints[9];

    int tesselation;
    BSP_VERTEX * vertices;
    GLuint * indices;

    //arrays for multi_draw_arrays
    int * trianglesPerRow;
    unsigned int ** rowIndexPointers;

    BSP_BIQUADRATIC_PATCH() : vertices(NULL)
    {}
    ~BSP_BIQUADRATIC_PATCH()
    {
        if (vertices)
            delete[] vertices;
        vertices = NULL;

        if (indices)
            delete[] indices;
        indices = NULL;
    }
};

//curved surface
class BSP_PATCH
{
public:
    int textureIndex;
    int lightmapIndex;
    int width, height;

    int numQuadraticPatches;
    BSP_BIQUADRATIC_PATCH * quadraticPatches;
};

//texture as found in file
class BSP_LOAD_TEXTURE
{
public:
    char name[64];
    int flags, contents;	//unknown
};

//lightmap as found in file
class BSP_LOAD_LIGHTMAP
{
public:
    GLubyte lightmapData[128 * 128 * 3];
};


//leaf of bsp tree as found in file
class BSP_LOAD_LEAF
{
public:
    int cluster;	//cluster index for visdata
    int area;		//areaportal area
    int mins[3];	//min x,y,z (bounding box)
    int maxs[3];
    int firstLeafFace;	//first index in leafFaces array
    int numFaces;
    int firstLeafBrush;	//first index into leaf brushes array
    int numBrushes;
};

//leaf of bsp tree as stored
class BSP_LEAF
{
public:
    int cluster;	//cluster index for visdata
    glm::vec3 boundingBoxVertices[8];
    int firstLeafFace;	//first index in leafFaces array
    int numFaces;
};

//node of BSP tree
class BSP_NODE
{
public:
    int planeIndex;
    int front, back;	//child nodes
    int mins[3];	//min x,y,z (bounding box)
    int maxs[3];
};

//VIS data table
class BSP_VISIBILITY_DATA
{
public:
    int numClusters;
    int bytesPerCluster;
    GLubyte * bitset;

    BSP_VISIBILITY_DATA()
    {}
    ~BSP_VISIBILITY_DATA()
    {
        if (bitset)
            delete[] bitset;
        bitset = NULL;
    }
};


class BSP : public SceneNode
{
public:
    BSP();
    ~BSP();

    bool load(const char* filename);
    bool render(RenderAction* act);

private:
    bool loadVertices(FILE* file);
    bool loadFaces(FILE* file);
    bool loadBSPData(FILE* file);

private:
    int _vb;

    // header
    BSP_HEADER _header;

    // vertices
    int _numVertices;
    BSP_VERTEX* _vertices;

    // faces
    int _numTotalFaces;

    BSP_FACE_DIRECTORY_ENTRY * _faceDirectory;

    // polygon faces
    int _numPolygonFaces;
    BSP_POLYGON_FACE * _polygonFaces;

    // mesh faces
    int * _meshIndices;
    int _numMeshFaces;
    BSP_MESH_FACE * _meshFaces;

    // patches
    int _numPatches;
    BSP_PATCH * _patches;
};

SK_END_NAMESPACE

#endif

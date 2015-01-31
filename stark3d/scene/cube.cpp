#include "cube.h"
#include <glload/gl_3_3.h>

namespace Scene {

Cube::Cube() : _vb(0)
{
    const float vertexData[] = {
        //  position             normal
        -50.0f,  50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
         50.0f, -50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
         50.0f,  50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
                                               
        -50.0f,  50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
        -50.0f, -50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
         50.0f, -50.0f,  50.0f,  0.0f,  0.0f,  1.0f,
                                        
         50.0f, -50.0f, -50.0f,  0.0f,  0.0f, -1.0f,
        -50.0f,  50.0f, -50.0f,  0.0f,  0.0f, -1.0f,
         50.0f,  50.0f, -50.0f,  0.0f,  0.0f, -1.0f,
                                        
        -50.0f, -50.0f, -50.0f,  0.0f,  0.0f, -1.0f,
        -50.0f,  50.0f, -50.0f,  0.0f,  0.0f, -1.0f,
         50.0f, -50.0f, -50.0f,  0.0f,  0.0f, -1.0f,

        -50.0f, -50.0f, -50.0f, -1.0f,  0.0f,  0.0f,
        -50.0f, -50.0f,  50.0f, -1.0f,  0.0f,  0.0f,
        -50.0f,  50.0f,  50.0f, -1.0f,  0.0f,  0.0f,
                                               
        -50.0f,  50.0f, -50.0f, -1.0f,  0.0f,  0.0f,
        -50.0f, -50.0f, -50.0f, -1.0f,  0.0f,  0.0f,
        -50.0f,  50.0f,  50.0f, -1.0f,  0.0f,  0.0f,
                                               
         50.0f, -50.0f,  50.0f,  1.0f,  0.0f,  0.0f,
         50.0f, -50.0f, -50.0f,  1.0f,  0.0f,  0.0f,
         50.0f,  50.0f,  50.0f,  1.0f,  0.0f,  0.0f,
                                               
         50.0f, -50.0f, -50.0f,  1.0f,  0.0f,  0.0f,
         50.0f,  50.0f, -50.0f,  1.0f,  0.0f,  0.0f,
         50.0f,  50.0f,  50.0f,  1.0f,  0.0f,  0.0f,
                                               
        -50.0f,  50.0f,  50.0f,  0.0f,  1.0f,  0.0f,
         50.0f,  50.0f,  50.0f,  0.0f,  1.0f,  0.0f,
         50.0f,  50.0f, -50.0f,  0.0f,  1.0f,  0.0f,
                                               
        -50.0f,  50.0f, -50.0f,  0.0f,  1.0f,  0.0f,
        -50.0f,  50.0f,  50.0f,  0.0f,  1.0f,  0.0f,
         50.0f,  50.0f, -50.0f,  0.0f,  1.0f,  0.0f,
                                               
         50.0f, -50.0f,  50.0f,  0.0f, -1.0f,  0.0f,
        -50.0f, -50.0f,  50.0f,  0.0f, -1.0f,  0.0f,
         50.0f, -50.0f, -50.0f,  0.0f, -1.0f,  0.0f,
                                               
        -50.0f, -50.0f,  50.0f,  0.0f, -1.0f,  0.0f,
        -50.0f, -50.0f, -50.0f,  0.0f, -1.0f,  0.0f,
         50.0f, -50.0f, -50.0f,  0.0f, -1.0f,  0.0f,
    };
    
    glGenBuffers(1, (GLuint*)&_vb);
    glBindBuffer(GL_ARRAY_BUFFER, _vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Cube::~Cube()
{
    if (_vb) { glDeleteBuffers(1, (GLuint*)&_vb); _vb = 0; }
}

bool Cube::render()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vb);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    int stride(sizeof(float)*3 + sizeof(float)*3);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)(3*sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    return true;
}

} // end namespace
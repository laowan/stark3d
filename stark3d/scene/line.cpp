#include "line.h"
#include <glload/gl_3_3.h>

namespace Scene {

    Line::Line() : _vb(0)
    {
        const float vertexData[] = {
            150.0f, 150.0f, 150.0f,
            -150.0f, -150.0f, -150.0f,
        };

        glGenBuffers(1, (GLuint*)&_vb);
        glBindBuffer(GL_ARRAY_BUFFER, _vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Line::~Line()
    {
        if (_vb) { glDeleteBuffers(1, (GLuint*)&_vb); _vb = 0; }
    }

    bool Line::render()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vb);

        glEnableVertexAttribArray(0);

        int stride(sizeof(float)* 3);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

        glDrawArrays(GL_LINES, 0, 2);

        glDisableVertexAttribArray(0);

        return true;
    }

} // end namespace
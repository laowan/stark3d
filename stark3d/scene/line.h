#ifndef _LINE_H
#define _LINE_H

#include "node.h"
#include <glm/glm.hpp>

namespace Scene {

    class Line : public SceneNode
    {
    public:
        Line(glm::vec3& point1, glm::vec3& point2);
        ~Line();

        bool render();

    private:
        int _vb;
    };

}

#endif
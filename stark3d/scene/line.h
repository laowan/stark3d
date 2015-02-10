#ifndef _LINE_H
#define _LINE_H

#include "node.h"
#include <glm/glm.hpp>

SK_BEGIN_NAMESPACE

class Line : public SceneNode
{
public:
    Line();
    Line(glm::vec3& point1, glm::vec3& point2);
    ~Line();

    bool render(RenderAction* act);

private:
    int _vb;
};

SK_END_NAMESPACE

#endif
#ifndef _LINE_H
#define _LINE_H

#include "node.h"
#include <glm/glm.hpp>

SK_BEGIN_NAMESPACE

class Line : public SceneNode
{
public:
    Line(glm::vec3& point1 = glm::vec3(0.0,0.0,0.0), glm::vec3& point2 = glm::vec3(0.0,0.0,0.0));
    ~Line();
    std::string type() { return "Line"; }

    void reset(glm::vec3& point1, glm::vec3& point2);

    bool render(RenderAction* act);

private:
    int _vb;
};

SK_END_NAMESPACE

#endif
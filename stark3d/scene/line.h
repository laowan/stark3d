#ifndef _LINE_H
#define _LINE_H

#include "scene.h"

namespace Scene {

    class Line : public SceneNode
    {
    public:
        Line();
        ~Line();

        bool render();

    private:
        int _vb;
    };

}

#endif
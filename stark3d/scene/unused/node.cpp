#include "node.h"
#include <iostream>

SK_BEGIN_NAMESPACE

// http://stackoverflow.com/questions/1649027/how-do-i-print-out-a-tree-structure
void SceneNode::print(std::string prefix)
{
    std::cout << prefix << " + " << _handle << "  " << type() << std::endl;
    for (size_t i = 0; i < _children.size(); i++)
    {
        if (i == _children.size() - 1)
            _children.at(i)->print(prefix + "  |");
        else
            _children.at(i)->print(prefix + "  |");
    }
}

SK_END_NAMESPACE

#pragma once

#include "global.h"
#include <string>

SK_BEGIN_NAMESPACE

class Object
{
public:
    Object() {}
    virtual ~Object() {}
    const std::string getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

private:
    std::string _name;
};

SK_END_NAMESPACE
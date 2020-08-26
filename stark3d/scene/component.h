#pragma once

#include "global.h"

SK_BEGIN_NAMESPACE

class Entity;
class Transform;

class Component
{
public:
    Entity* getEntity() const { return _entity; }
private:
    Entity* _entity;
};

SK_END_NAMESPACE
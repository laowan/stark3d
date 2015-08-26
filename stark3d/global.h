#ifndef _GLOBAL_H
#define _GLOBAL_H

typedef signed char int8;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

#define SK_BEGIN_NAMESPACE namespace SK {
#define SK_END_NAMESPACE }
#define SK_USE_NAMESPACE using namespace SK;

#include <glm/gtc/type_ptr.hpp>

#endif
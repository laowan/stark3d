#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

extern unsigned char* makeDistanceMap(unsigned char *img, int width, int height, int distanceMapSpread);

// extern void skScreenshot(const char* file);
// extern void skCreateScene1();
// extern void skCreateScene2();

#if defined(_WIN32) || defined(WIN32)
typedef unsigned __int64 SKUInt64;

typedef struct timeval
{
    SKUInt64 tv_sec;
    SKUInt64 tv_usec;
} timeval;

int gettimeofday(struct timeval * tp, struct timezone * tzp);
#else 
#include <sys/time.h>
#endif

#define MAX_TIME_TOLERANCE 2000000000

SKUInt64 CurrentTime();

#endif

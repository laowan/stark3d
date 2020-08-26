#ifndef SK_WORLD_H
#define SK_WORLD_H

#include "global.h"
#include "camera.h"
#include <string>

SK_BEGIN_NAMESPACE

class FontAtlasCache;

class World
{
    SK_DECLARE_IMPL(World);
public:
    World();
    ~World();

    bool load(const std::string& path);
    void render(Camera* camera);

    FontAtlasCache* getFontAtlasCache();
private:
    Camera* camera;
};

SK_END_NAMESPACE

#endif
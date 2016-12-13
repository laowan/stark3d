#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include "gameobject.h"

class GameLevel
{
public:
    GameLevel();
    void load(std::string file, int width, int height);
    void draw(SK::Sprite* sprite);
private:
    void init(std::vector<std::vector<int>> tileData, int width, int height);

public:
    std::vector<GameObject> bricks;
};

#endif

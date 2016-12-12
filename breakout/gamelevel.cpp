#include "gamelevel.h"

#include <fstream>
#include <sstream>

GameLevel::GameLevel()
{
}

void GameLevel::load(std::string file, int width, int height)
{
    this->bricks.clear();

    int tileCode;
    std::vector<std::vector<int>> tileData;
    std::string line;
    std::ifstream fstream(file);
    if (fstream)
    {
        while (std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<int> row;
            while (sstream >> tileCode)
                row.push_back(tileCode);
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            this->init(tileData, width, height);
    }
}

void GameLevel::draw()
{
}

void GameLevel::init(std::vector<std::vector<int>> tileData, int width, int height)
{
}


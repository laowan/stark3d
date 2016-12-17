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

void GameLevel::draw(SK::Sprite *sprite)
{
    for (size_t i = 0; i < bricks.size(); ++i)
    {
        if (!bricks[i].destoryed)
            bricks[i].draw(sprite);
    }
}

void GameLevel::init(std::vector<std::vector<int>> tileData, int width, int height)
{
    size_t heightCnt = tileData.size();
    size_t widthCnt = tileData[0].size();
    float unitWidth = width / (float)(widthCnt);
    float unitHeight = height / (float)(heightCnt);

    for (int y = 0; y < heightCnt; ++y)
    {
        for (int x = 0; x < widthCnt; ++x)
        {
            int data = tileData[y][x];
            if (data == 1) // solid
            {
                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(pos, size,
                    glm::vec3(0.8f, 0.8f, 0.7f), glm::vec2(0.0f, 0.0f),
                    SK::Module::resMan().getTexture("block_solid"),
                    SK::Module::resMan().getShader("sprite"));
                obj.isSolid = true;
                this->bricks.push_back(obj);
            }
            else if (data > 1)
            {
                glm::vec3 color = glm::vec3(1.0f);
                if (data == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (data == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (data == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (data == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unitWidth * x, unitHeight * y);
                glm::vec2 size(unitWidth, unitHeight);
                GameObject obj(pos, size, color, glm::vec2(0.0f, 0.0f),
                    SK::Module::resMan().getTexture("block"),
                    SK::Module::resMan().getShader("sprite"));
                this->bricks.push_back(obj);
            }
        }
    }
}


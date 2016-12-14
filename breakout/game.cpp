
#include "game.h"

Game::Game(unsigned int w, unsigned int h)
    : state(GAME_ACTIVE), keys(), width(w), height(h), currentLevel(0)
{
    sprite = NULL;
}

Game::~Game()
{
    if (sprite) delete sprite;
    if (player) delete player;
}

void Game::init(int w, int h)
{
    width = w;
    height = h;

    GameLevel level;
    level.load("./resource/level.txt", width, height*0.5);
    levels.push_back(level);

    SK::Module::resMan().loadShader("sprite");
    SK::Module::resMan().loadTexture("block");
    SK::Module::resMan().loadTexture("block_solid");
    SK::Module::resMan().loadTexture("awesomeface");
    SK::Module::resMan().loadTexture("paddle");

    sprite = new SK::Sprite;

    glm::vec2 playerSize(50.0f, 10.0f);
    glm::vec2 playerPos = glm::vec2(
        (float)w / 2 - playerSize.x / 2, (float)h - playerSize.y);

    player = new GameObject(playerPos, playerSize, glm::vec3(1.0f), glm::vec2(0.0f),
        SK::Module::resMan().getTexture("paddle"), SK::Module::resMan().getShader("sprite"));

}

void Game::update(float dt)
{

}

void Game::processInput(unsigned char key, float dt)
{
    if (state == GAME_ACTIVE)
    {
        float velocity(10.0f);
        if (key == 'a')
        {
            if (player->position.x > 0)
                player->position.x -= velocity;
            else
                player->position.x = 0.0;
        }
        else if (key == 'd')
        {
            if (player->position.x + player->size.x < width)
                player->position.x += velocity;
            else
                player->position.x = width - player->size.x;
        }
    }
}

void Game::render()
{
    levels[currentLevel].draw(sprite);
    player->draw(sprite);
}
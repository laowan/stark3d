
#include "game.h"


Game::Game(unsigned int w, unsigned int h)
    : state(GAME_ACTIVE), keys(), width(w), height(h), currentLevel(0)
{
    sprite = NULL;
}

Game::~Game()
{
    if (sprite) delete sprite;
}

void Game::init(int w, int h)
{
    width = w;
    height = h;

    sprite = new SK::Sprite;

    GameLevel level;
    level.load("./resource/level.txt", width, height);
    levels.push_back(level);

    SK::Module::resMan().loadShader("sprite");
    SK::Module::resMan().loadTexture("block");
    SK::Module::resMan().loadTexture("block_solid");
}

void Game::update(float dt)
{

}

void Game::processInput(float dt)
{

}

void Game::render()
{
    levels[currentLevel].draw(sprite);
}
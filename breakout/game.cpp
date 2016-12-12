
#include "game.h"


Game::Game(unsigned int w, unsigned int h)
: state(GAME_ACTIVE), keys(), width(w), height(h)
{

}

Game::~Game()
{

}

void Game::init(int w, int h)
{
    width = w;
    height = h;

    GameLevel level;
    level.load("./resource/level.txt", width, height);
    levels.push_back(level);
}

void Game::update(float dt)
{

}


void Game::processInput(float dt)
{

}

void Game::render()
{

}
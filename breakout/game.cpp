
#include "game.h"

Game::Game(unsigned int w, unsigned int h)
    : state(GAME_ACTIVE), keys(), width(w), height(h), currentLevel(0)
{
    sprite = NULL;
    ball = NULL;
}

Game::~Game()
{
    if (sprite) delete sprite;
    if (player) delete player;
    if (ball) delete ball;
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

    float ballRadius = 10.0f;
    glm::vec2 ballPos = playerPos + glm::vec2(playerSize.x/2 - ballRadius, -ballRadius*2);
    ball = new Ball(ballPos, ballRadius, glm::vec2(100.0f, -100.0f),
        SK::Module::resMan().getTexture("awesomeface"), SK::Module::resMan().getShader("sprite"));

}

void Game::update(float dt)
{
    ball->move(dt, width);
    doCollisionTest();
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
        else if (key == ' ')
        {
            ball->setStuck(false);
        }
    }
}

void Game::render()
{
    levels[currentLevel].draw(sprite);
    player->draw(sprite);
    ball->draw(sprite);
}

void Game::doCollisionTest()
{
    for (GameObject &brick : levels[currentLevel].bricks)
    {
        if (!brick.destoryed)
        {
            if (checkCollision(ball, &brick))
            {
                if (!brick.isSolid)
                    brick.destoryed = true;
            }
        }
    }
}

bool Game::checkCollision(GameObject *objOne, GameObject *objTwo)
{

    bool collisionX = objOne->position.x + objOne->size.x >= objTwo->position.x &&
        objTwo->position.x + objTwo->size.x >= objOne->position.x;

    bool collisionY = objOne->position.y + objOne->size.y >= objTwo->position.y &&
        objTwo->position.y + objTwo->size.y >= objOne->position.y;

    return collisionX && collisionY;
}

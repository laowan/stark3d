
#include "game.h"

const float sBallRadius = 10.0f;
const glm::vec2 sBallInitVelocity(100.0f, -100.0f);
const glm::vec2 sPlayerSize(50.0f, 10.0f);

Game::Game(unsigned int w, unsigned int h)
    : state(GAME_ACTIVE), keys(), width(w), height(h), currentLevel(0)
{
    sprite = NULL;
    ball = NULL;
    particles = NULL;
}

Game::~Game()
{
    if (sprite) delete sprite;
    if (player) delete player;
    if (ball) delete ball;
    if (particles) delete particles;
}

void Game::init(int w, int h)
{
    width = w;
    height = h;

    GameLevel level;
    level.load("./resource/level.txt", width, height*0.5);
    levels.push_back(level);

    SK::Module::resMan().loadShader("sprite");
    SK::Module::resMan().loadShader("particle");
    SK::Module::resMan().loadTexture("block");
    SK::Module::resMan().loadTexture("block_solid");
    SK::Module::resMan().loadTexture("awesomeface");
    SK::Module::resMan().loadTexture("paddle");
    SK::Module::resMan().loadTexture("particle");

    sprite = new SK::Sprite;

    // player
    glm::vec2 playerSize(sPlayerSize);
    glm::vec2 playerPos = glm::vec2((float)w / 2 - playerSize.x / 2, (float)h - playerSize.y);

    player = new GameObject(playerPos, playerSize, glm::vec3(1.0f), glm::vec2(0.0f),
        SK::Module::resMan().getTexture("paddle"), SK::Module::resMan().getShader("sprite"));

    // ball
    float ballRadius = sBallRadius;
    glm::vec2 ballPos = playerPos + glm::vec2(playerSize.x/2 - ballRadius, -ballRadius*2);
    ball = new Ball(ballPos, ballRadius, sBallInitVelocity,
        SK::Module::resMan().getTexture("awesomeface"), SK::Module::resMan().getShader("sprite"));

    // particle
    particles = new ParticleGenerator(SK::Module::resMan().getShader("particle"),
        SK::Module::resMan().getTexture("particle"), 500);

}

void Game::update(float dt)
{
    ball->move(dt, width);
    if (ball->position.y > height)
    {
        reset();
    }
    doCollisionTest();

    if (!ball->isStuck())
    {
        particles->update(dt, ball, 2, glm::vec2(ball->radius()/2));
    }
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
    particles->draw();
    ball->draw(sprite);
}

void Game::reset()
{
    levels[currentLevel].reset();
    player->position = glm::vec2(width / 2.0f - sPlayerSize.x / 2, (float)height - sPlayerSize.y);
    ball->position = player->position + glm::vec2(sPlayerSize.x/2 - sBallRadius, -sBallRadius*2);
}

void Game::doCollisionTest()
{
    // check the ball and the bricks
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

    // check the ball and the player
    if (!ball->isStuck() && checkCollision(ball, player))
    {
        float center = player->position.x + player->size.x / 2;
        float distance = ball->position.x + ball->radius() - center;
        float percentage = distance / (player->size.x / 2);
        float strength = 2.0f;

        glm::vec2 oldVelocity = ball->velocity;
        ball->velocity.x = sBallInitVelocity.x * percentage * strength;
        ball->velocity.y = -1*abs(ball->velocity.y);
        ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
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

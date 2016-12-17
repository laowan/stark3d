#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "gamelevel.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // Constructor/Destructor
    Game(unsigned int w = 0, unsigned int h = 0);
    ~Game();
    
    // Initialize game state (load all shaders/textures/levels)
    void init(int w, int h);
    
    // GameLoop
    void processInput(unsigned char key, float dt);
    void update(float dt);
    void render();

    void doCollisionTest();

private:
    bool checkCollision(GameObject *objOne, GameObject *objTwo);

public:
    // Game state
    GameState         state;
    bool              keys[1024];
    unsigned int      width, height;
    std::vector<GameLevel> levels;
    int currentLevel;
    GameObject *player;
    SK::Sprite *sprite;
    Ball *ball;
};

#endif
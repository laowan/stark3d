#ifndef GAME_H
#define GAME_H

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
    void processInput(float dt);
    void update(float dt);
    void render();

public:
    // Game state
    GameState         state;
    bool              keys[1024];
    unsigned int      width, height;
    std::vector<GameLevel> levels;
    int currentLevel;
    SK::Sprite* sprite;
};

#endif
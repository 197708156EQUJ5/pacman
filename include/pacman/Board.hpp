#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/CharacterManager.hpp"
#include "pacman/GhostModeTimer.hpp"
#include "pacman/Level.hpp"
#include "pacman/SpriteSheet.hpp"

#include <SDL2/SDL.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

namespace pacman
{

class Board
{
public:

    Board();
    ~Board();
    
    bool init();
    void update(double deltaTime);
    void draw();
    void setUserDirection(Direction direction);

private:    
    
    std::unique_ptr<SpriteSheet> spriteSheet;
    std::unique_ptr<CharacterManager> characterManager;
    std::unique_ptr<GhostModeTimer> ghostModeTimer;
    std::unique_ptr<std::thread> ghostModeThread;
    std::vector<Cell> maze;
    std::shared_ptr<Pacman> pacman;
    std::vector<std::shared_ptr<Ghost>> ghosts;
    Direction userDirection;
    std::vector<std::pair<int, GhostMode>> transitionDelays;

    int score;
    int lives;
    int level;
    int count;
    std::chrono::time_point<std::chrono::system_clock> gameStartTime;
    
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;

    void drawBoard();
    void drawText();
    void drawMaze();

    void drawCharacter(std::shared_ptr<Character> character);
    void drawLargeTile(int tileX, int tileY, int tileSrcCol, int tileSrcRow);
    void drawPacman();
    void drawGhosts();

    void drawScore();
    void drawLives();
    void drawFruits();
    
    void updatePacman();
    void updateGhosts();

    void transitionGhostModeHandler(GhostMode ghostMode);
};

} // namespace

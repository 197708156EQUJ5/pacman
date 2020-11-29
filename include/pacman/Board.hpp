#pragma once

#include "pacman/Direction.hpp"
#include "pacman/CharacterManager.hpp"
#include "pacman/LevelDesign.hpp"
#include "pacman/SpriteSheet.hpp"

#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <memory>
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
    std::vector<Cell> maze;
    std::vector<Cell> legalTiles;
    std::shared_ptr<Pacman> pacman;
    std::vector<std::shared_ptr<Ghost>> ghosts;

    Direction userDirection;
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

    void drawPacman();
    void updatePacman();
    bool canMovePacman();
    bool canChangeDirection();
    void drawGhosts();
    void updateGhosts();
    bool canMoveGhost(std::shared_ptr<Ghost> ghost);
    bool canMove(Cell cell);
    void drawCharacter(std::shared_ptr<Character> character);

    std::vector<Cell> getNextTiles(std::shared_ptr<Character> character);

    void drawScore();
    void drawLives();
    void drawFruits();

};

} // namespace

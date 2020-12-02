#pragma once

#include "pacman/AdjacentTile.hpp"
#include "pacman/Direction.hpp"
#include "pacman/CharacterManager.hpp"
#include "pacman/Level.hpp"
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
    void drawGhosts();
    void updateGhosts();
    bool canMoveGhost(std::shared_ptr<Ghost> ghost);
    void drawCharacter(std::shared_ptr<Character> character);

    void drawScore();
    void drawLives();
    void drawFruits();
    
    void printCells(AdjacentTile adjacentTile, std::shared_ptr<Character> character);

};

} // namespace

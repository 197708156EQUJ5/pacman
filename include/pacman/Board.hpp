#pragma once

#include "pacman/LevelDesign.hpp"
#include "pacman/SpriteSheet.hpp"

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>

namespace pacman
{

class Board
{
public:

    Board() = default;
    ~Board();
    
    //Screen dimension constants
    static const int WIDTH = 672;
    static const int HEIGHT = 864;
    static const int SS_COLUMNS = 32;
    static const int SS_ROW = 20;
    
    bool init();
    void update(double deltaTime);
    void draw();

private:
    
    
    std::unique_ptr<SpriteSheet> spriteSheet;
    std::vector<Cell> level;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;
};

} // namespace

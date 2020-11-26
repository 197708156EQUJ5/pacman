#pragma once

#include "pacman/Direction.hpp"
#include "pacman/CharacterManager.hpp"
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

    Board();
    ~Board();
    
    bool init();
    void update(double deltaTime);
    void draw();
    void setUserDirection(Direction direction);

private:    
    
    std::unique_ptr<SpriteSheet> spriteSheet;
    std::unique_ptr<CharacterManager> characterManager;
    std::vector<Cell> level;

    Direction userDirection;
    
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;
};

} // namespace

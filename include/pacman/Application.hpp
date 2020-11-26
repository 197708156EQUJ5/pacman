#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include "pacman/Board.hpp"

namespace pacman
{

class Application
{
public:
    
    Application();
    ~Application() = default;

    void loop();

private:
    
    std::unique_ptr<Board> board;
    SDL_Event event;
};

} // namespace

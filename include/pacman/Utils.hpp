#pragma once

#include "Direction.hpp"

#include <SDL2/SDL.h>

namespace pacman
{

SDL_Surface *load_bmp(char const *path);

Direction getOpposite(Direction direction);

}

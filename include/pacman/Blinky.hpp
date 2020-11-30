#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Blinky : public Ghost
{
public:

    Blinky();
    ~Blinky() = default;
    
    int getSrcCol();
    int getSrcRow();
};

} // namespace pacman


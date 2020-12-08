#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Inky : public Ghost
{
public:

    Inky();
    ~Inky() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getReleaseCounter();
};

} // namespace pacman


#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Pinky : public Ghost
{
public:

    Pinky();
    ~Pinky() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getReleaseCounter();
};

} // namespace pacman


#pragma once

#include "pacman/Ghost.hpp"

namespace pacman
{

class Clyde : public Ghost
{
public:

    Clyde();
    ~Clyde() = default;
    
    int getSrcCol();
    int getSrcRow();
    int getReleaseCounter();
    bool preExitingCheck();
};

} // namespace pacman


#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int col = 0, int row = 0, Direction direction = Direction::LEFT);
    ~Ghost() = default;
    
};

} // namespace pacman


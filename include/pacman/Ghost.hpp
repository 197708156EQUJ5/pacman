#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, Direction direction = Direction::LEFT);
    ~Ghost() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();

};

} // namespace pacman


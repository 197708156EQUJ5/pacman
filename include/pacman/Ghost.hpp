#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Ghost : public Character
{
public:

    Ghost(int x = 0, int y = 0, Direction direction = Direction::LEFT, bool isOddMove = false);
    ~Ghost() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);
};

} // namespace pacman


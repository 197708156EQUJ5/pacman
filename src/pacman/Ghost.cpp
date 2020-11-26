#include "pacman/Ghost.hpp"

namespace pacman
{

Ghost::Ghost(int x, int y, Direction direction, bool isOddMove) : 
    Character(x, y, direction, isOddMove)
{
}

void Ghost::move()
{
    if (direction == Direction::LEFT)
    {
        x++;
    }
}

void Ghost::changeDirection(Direction direction)
{
    this->direction = direction;
}

}

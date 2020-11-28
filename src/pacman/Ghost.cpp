#include "pacman/Ghost.hpp"

namespace pacman
{

Ghost::Ghost(int x, int y, Direction direction, bool isOddMove, bool isHome) : 
    Character(x, y, direction, isOddMove),
    isGhostHome(isHome)
{
}

void Ghost::move()
{
    if (direction == Direction::LEFT)
    {
        x -= 9;
    }
    else if (direction == Direction::RIGHT)
    {
        x += 9;
    }
    else if (direction == Direction::DOWN)
    {
        y += 9;
    }
    else if (direction == Direction::UP)
    {
        y -= 9;
    }
    isOddMove = !isOddMove;    
}

void Ghost::changeDirection(Direction direction)
{
    this->direction = direction;
}

bool Ghost::isHome()
{
    return this->isGhostHome;
}

}

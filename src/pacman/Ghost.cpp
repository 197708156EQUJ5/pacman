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
        x -= GhostConstants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::RIGHT)
    {
        x += GhostConstants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::DOWN)
    {
        y += GhostConstants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::UP)
    {
        y -= GhostConstants::MAXIMUM_PIXEL_SPEED;
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

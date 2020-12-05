#include "pacman/Ghost.hpp"

namespace pacman
{

Ghost::Ghost(int x, int y, Direction direction, bool isHome, bool isCounterActive) : 
    Character(x, y, direction),
    isGhostHome(isHome),
    pelletCounter(0),
    isCounterActive(isCounterActive)
{
}

void Ghost::move()
{
    if (direction == Direction::LEFT)
    {
        x -= Constants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::RIGHT)
    {
        x += Constants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::DOWN)
    {
        y += Constants::MAXIMUM_PIXEL_SPEED;
    }
    else if (direction == Direction::UP)
    {
        y -= Constants::MAXIMUM_PIXEL_SPEED;
    }
    /*
    if (direction == Direction::LEFT)
    {
        x -= Constants::MAXIMUM_PIXEL_SPEED * Constants::TILE_DISPLAY_RATIO;
    }
    else if (direction == Direction::RIGHT)
    {
        x += Constants::MAXIMUM_PIXEL_SPEED * Constants::TILE_DISPLAY_RATIO;
    }
    else if (direction == Direction::DOWN)
    {
        y += Constants::MAXIMUM_PIXEL_SPEED * Constants::TILE_DISPLAY_RATIO;
    }
    else if (direction == Direction::UP)
    {
        y -= Constants::MAXIMUM_PIXEL_SPEED * Constants::TILE_DISPLAY_RATIO;
    }
    */
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

bool Ghost::setHome(bool isHome)
{
    this->isGhostHome = isHome;
}

}

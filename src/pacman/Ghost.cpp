#include "pacman/Ghost.hpp"

namespace pacman
{

Ghost::Ghost(int x, int y, Direction direction, bool isHome, bool isExiting, bool isCounterActive) : 
    Character(x, y, direction),
    isGhostHome(isHome),
    isExitingHome(isExiting),
    pelletCounter(0),
    isCounterActive(isCounterActive)
{
    this->directionQueue.push(Direction::NONE);
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

void Ghost::setHome(bool isHome)
{
    this->isGhostHome = isHome;
}

bool Ghost::isExiting()
{
    return this->isExitingHome;
}

void Ghost::addNextDirection(Direction direction)
{
    this->directionQueue.push(direction);
}

Direction Ghost::peekNextDirection()
{
    return this->directionQueue.front();
}

Direction Ghost::getNextDirection()
{
    Direction direction = peekNextDirection();
    this->directionQueue.pop();

    return direction;
}

void Ghost::setCurrentTile(Cell tile)
{
    this->previousTile = this->currentTile;
    this->currentTile = tile;
}

bool Ghost::hasTileChanged()
{
    return this->previousTile != this->currentTile;
}

Cell Ghost::getCurrentTile()
{
    return this->currentTile;
}

std::queue<Direction> Ghost::getQueue()
{
    return this->directionQueue;
}

}

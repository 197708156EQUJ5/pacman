#include "pacman/Ghost.hpp"

#include <iostream>

namespace pacman
{

Ghost::Ghost(int x, int y, int xTarget, int yTarget, Direction direction, 
        bool isHome, bool isExiting, bool isCounterActive) :
    Character(x, y, direction),
    xTarget(xTarget),
    yTarget(yTarget),
    isGhostHome(isHome),
    isExitingHome(isExiting),
    dotCounter(0),
    isCounterActive(isCounterActive),
    exitStrategyIndex(0),
    exitStrategy{},
    preCheck(true)
{
    this->directionQueue.push(Direction::NONE);
}

void Ghost::move()
{
    if (!collided)
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

void Ghost::setHome(bool isHome)
{
    this->isGhostHome = isHome;
}

bool Ghost::isExiting()
{
    return this->isExitingHome;
}

void Ghost::setExiting(bool isExiting)
{
    this->isExitingHome = isExiting;
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

void Ghost::setMode(GhostMode mode)
{
    this->ghostMode = mode;
}

GhostMode Ghost::getMode()
{ 
    return this->ghostMode;
}

Cell Ghost::getTarget()
{
    return Cell{xTarget, yTarget};
}

std::queue<Direction> Ghost::getQueue()
{
    return this->directionQueue;
}

std::pair<Cell, Direction> Ghost::peekNextExitStep()
{
    if (exitStrategyIndex == exitStrategy.size())
    {
        return std::pair<Cell, Direction>{Cell{0,0}, Direction::NONE};
    }
    std::pair<Cell, Direction> nextStep = exitStrategy.at(exitStrategyIndex);

    return nextStep;
}

void Ghost::advanceNextExitStep()
{
    exitStrategyIndex++;
}

void Ghost::resetDotCounter()
{
    this->dotCounter = 0;
}

void Ghost::increaseDotCounter()
{
    this->dotCounter++;
}

void Ghost::setDotCounterActive(bool isActive)
{
    this->isCounterActive = isActive;
}

int Ghost::getDotCounter()
{
    return this->dotCounter;
}

bool Ghost::isDotCounterActive()
{
    return this->isCounterActive;    
}

}

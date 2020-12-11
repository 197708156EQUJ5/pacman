#include "pacman/CharacterManager.hpp"

#include "pacman/Level.hpp"
#include "pacman/GhostMode.hpp"
#include "pacman/Utils.hpp"

#include <algorithm>
#include <bits/stdc++.h>
#include <iomanip>
#include <typeinfo>

namespace pacman
{
    
CharacterManager::CharacterManager() :
    releaseOrderIndex(0),
    mtx(std::make_unique<std::mutex>())
{
    pacman = std::make_shared<Pacman>();
    blinky = std::make_shared<Blinky>();
    pinky = std::make_shared<Pinky>();
    inky = std::make_shared<Inky>();
    clyde = std::make_shared<Clyde>();
    
    releaseOrder = {pinky, inky, clyde};
}

std::shared_ptr<Pacman> CharacterManager::getPacman()
{
    return pacman;
}

std::vector<std::shared_ptr<Ghost>> CharacterManager::getGhosts()
{
    return {pinky, inky, blinky, clyde};
}

bool CharacterManager::canMovePacman()
{
    Direction direction = pacman->getDirection();

    if (direction == Direction::NONE)
    {
        return true;
    }

    int x = pacman->getX();
    int y = pacman->getY();
    AdjacentTile adjacentTile = Util::getAdjacentTiles<Pacman>(x, y, direction);

    return Level::isLegalMove(Util::convertToGrid(adjacentTile.fromDirection(direction)));
}

bool CharacterManager::canMoveGhost(std::shared_ptr<Ghost> ghost)
{
    int x = ghost->getX();
    int y = ghost->getY();
    Direction ghostDirection = ghost->getDirection();

    if (ghost->isHome() && !ghost->isExiting())
    {
        AdjacentTile homeAdjacentTile = Util::getAdjacentTiles<Ghost>(x, y, ghostDirection);
        std::vector<int> homeLegalDirections = findLegalDirections(homeAdjacentTile, ghost);

        if (ghostDirection == Direction::DOWN || ghostDirection == Direction::UP)
        {
            if (find(homeLegalDirections.begin(), homeLegalDirections.end(), (int)ghostDirection) != homeLegalDirections.end())
            {
                ghost->changeDirection(Util::getOpposite(ghostDirection));
            }
        }
        return true;
    }

    if (ghost->isExiting())
    {
        if (ghost->preExitingCheck())
        {
            ghost->changeDirection(Util::getOpposite(ghostDirection));
            return true;
        }
        std::pair<Cell, Direction> nextStep = ghost->peekNextExitStep();
        Cell nextStepCell = nextStep.first;
        Direction nextStepDirection = nextStep.second;
        //printf("%s: (%3d, %3d) nextStep - Cell: (%3d, %3d) direction: %d\n", typeid(*ghost).name(), 
        //        ghost->getX(), ghost->getY(), nextStepCell.col, nextStepCell.row, nextStepDirection);

        if (nextStepDirection == Direction::NONE)
        {
            ghost->addNextDirection(Direction::LEFT);
            ghost->setExiting(false);
            ghost->setHome(false);
            return true;
        }

        if (Cell{x, y} == nextStepCell)
        {
            //printf("Next pivot point (%3d, %3d) acheived. Setting direction: %d\n", ghost->getX(), ghost->getY(), nextStepDirection);
            ghost->changeDirection(nextStepDirection);
            ghost->advanceNextExitStep();
        }
        return true;
    }

    Direction peekDirection = ghost->peekNextDirection();
    AdjacentTile adjacentTile;
    if (peekDirection == Direction::NONE)
    {
        ghost->getNextDirection();
        adjacentTile = Util::getAdjacentTiles<Ghost>(x, y, ghostDirection);
    }
    else
    {
        adjacentTile = Util::getAdjacentTiles<Ghost>(x, y, peekDirection);
    }

    //Util::displayTiles<Pinky>(adjacentTile, ghost);

    ghost->setCurrentTile(Util::getCurrentCell(x, y));

    std::vector<int> legalDirections = findLegalDirections(adjacentTile, ghost);

    /*
    if (typeid(*ghost) == typeid(Pinky))
    {
        printf("(%3d, %3d) {", x, y);
        for (int dir : legalDirections)
        {
            printf("%d ", dir);
        }
        printf("}\n");
    }
    */

    selectNewDirection(adjacentTile, legalDirections, ghost);

    bool onTrackX = (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) && ((y + 4) % 8 == 0);
    bool onTrackY = (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) && ((x + 4) % 8 == 0);

    if (onTrackX || onTrackY)
    {
        Direction changedDirection = ghost->getNextDirection();
        /*
        if (typeid(*ghost) == typeid(Blinky))
        {
            printf("changing direction; %d\n", changedDirection);
        }
        */
        ghost->changeDirection(changedDirection);
    }

    return true;
}

std::vector<int> CharacterManager::findLegalDirections(AdjacentTile adjacentTile, std::shared_ptr<Ghost> ghost)
{
    int directionIndex = 1;
    std::vector<int> legalDirections;
    
    if (ghost->isExiting())
    {
        legalDirections.push_back((int)Direction::UP);
    }
    else
    {
        for (Cell cell : adjacentTile.tiles)
        {
            if (Level::isLegalMove(Util::convertToGrid(cell)) && Util::getCenter(cell) != ghost->getCurrentTile())
            {
                legalDirections.push_back(directionIndex);
            }
            directionIndex++;
        }
    }

    return legalDirections;
}

void CharacterManager::selectNewDirection(AdjacentTile adjacentTile, std::vector<int> legalDirections, std::shared_ptr<Ghost> ghost)
{
    Direction newDirection = Direction::NONE;
    if (legalDirections.size() == 1 && ghost->hasTileChanged())
    {
        newDirection = (Direction)legalDirections.at(0);
        ghost->addNextDirection(newDirection);
        /*
        if (typeid(*ghost) == typeid(Pinky))
        {
            printf("legal size: %d, tileChanged adding next direction; %d\n", legalDirections.size(), newDirection);
        }
        */
    }

    if (legalDirections.size() > 1 && ghost->hasTileChanged())
    {
        //printf("GhostMode[%s]: %d\n", typeid(*ghost).name(), ghost->getMode());
        switch (ghost->getMode())
        {
            case GhostMode::SCATTER:
            {
                if (typeid(*ghost) == typeid(Pinky))
                {
                    //printf("SCATTER %s", typeid(*ghost).name());
                }
                Cell targetCell = ghost->getTarget();
                findNextDirection(targetCell, adjacentTile, legalDirections, newDirection);
                if (typeid(*ghost) == typeid(Pinky))
                {
                    //printf("next direction; %d\n", newDirection);
                }
            }
            break;
            case GhostMode::CHASE:
            {
                printf("Handle CHASE case.\n");
                handleChaseMode(ghost, adjacentTile, legalDirections, newDirection);
            }
            break;
            case GhostMode::FRIGHTENED:
            {
                newDirection = (Direction)(legalDirections.at(std::rand() % legalDirections.size()));
            }
            break;
        }
        ghost->addNextDirection(newDirection);
        /*
        if (typeid(*ghost) == typeid(Pinky))
        {
            printf("legal size: %d, tileChanged adding next direction; %d\n", legalDirections.size(), newDirection);
        }
        */
    }
}

void CharacterManager::incrementDotCounter()
{
    for (std::shared_ptr<Ghost> ghost : getGhosts())
    {
        if (ghost->isDotCounterActive())
        {
            determineRelease(ghost);
            ghost->increaseDotCounter();
        }
    }
}

void CharacterManager::determineRelease(std::shared_ptr<Ghost> ghost)
{
    /*
    */
    //printf("%s Dot Ctr: %d Release Ctr: %d\n", typeid(*ghost).name(), ghost->getDotCounter(), ghost->getReleaseCounter());
    if (ghost->getDotCounter() == ghost->getReleaseCounter())
    {
        ghost->setExiting();
        ghost->setDotCounterActive(false);
        releaseOrderIndex++;
        if (releaseOrderIndex == releaseOrder.size())
        {
            return;
        }
        releaseOrder.at(releaseOrderIndex)->setDotCounterActive();
        //printf("Exiting: %s next release: %s releaseOrderIndex: %d\n", typeid(*ghost).name(), typeid(*releaseOrder.at(releaseOrderIndex)).name(), releaseOrderIndex);
    }
}

void CharacterManager::updateGhostMode(GhostMode ghostMode)
{
    mtx->lock();

    for (std::shared_ptr<Ghost> ghost : getGhosts())
    {
        ghost->setMode(ghostMode);
    }
    
    mtx->unlock();
}

void CharacterManager::findNextDirection(Cell targetCell, AdjacentTile adjacentTile, std::vector<int> legalDirections, Direction &newDirection)
{
    float shorterDistance = 10000000.0;
    int shorterDirection = INT_MAX;
    for (int d : legalDirections)
    {
        Cell current = adjacentTile.fromDirection((Direction)d);
        float distance = Util::distance(current.col, current.row, targetCell.col, targetCell.row);
        /*
        if (typeid(*ghost) == typeid(Pinky))
        {
            printf("\ndir: %d curr (%3d, %3d) target (%3d, %3d) distance: %.3f ", 
                d, current.col, current.row, target.col, target.row, distance);
        }
        */
        if (distance < shorterDistance || (distance == shorterDistance && d < shorterDirection))
        {
            shorterDistance = distance;
            shorterDirection = d;
            newDirection = (Direction) d;
        }
    }
}

void CharacterManager::handleChaseMode(std::shared_ptr<Ghost> ghost, AdjacentTile adjacentTile, 
        std::vector<int> legalDirections, Direction &newDirection)
{
    int x = pacman->getX();
    int y = pacman->getY();
    Direction pacmanDirection = pacman->getDirection();
    Cell targetCell = {0, 0};

    if (typeid(*ghost) == typeid(Blinky))
    {
        targetCell = Util::getCenter(Cell{x, y});
    }
    else if (typeid(*ghost) == typeid(Pinky))
    {
        targetCell = Util::getTileAhead(x, y, pacmanDirection, 4);
    }
    else if (typeid(*ghost) == typeid(Inky))
    {
        Cell pacmanOffset = Util::getTileAhead(x, y, pacmanDirection, 2);
        Cell blinkyCenter = Util::getCenter(blinky->getX(), blinky->getY());

        targetCell = {pacmanOffset.col * 2 - blinkyCenter.col, pacmanOffset.row * 2 - blinkyCenter.row};
    }
    else if (typeid(*ghost) == typeid(Clyde))
    {
        float distanceToPacman = Util::distance(ghost->getX(), ghost->getY(), pacman->getX(), pacman->getY()) / Constants::TILE_SIZE;

        if (distanceToPacman < ClydeConstants::CHASE_TILE_THRESHOLD)
        {
            targetCell = Util::getCenter(Cell{x, y});
        }
        else
        {
            targetCell = ghost->getTarget();
        }
    }
    findNextDirection(targetCell, adjacentTile, legalDirections, newDirection);
}

}

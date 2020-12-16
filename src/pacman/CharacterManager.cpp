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
    
CharacterManager::CharacterManager(std::function<void(int, Cell, std::shared_ptr<Ghost>)> ghostEaten) :
    releaseOrderIndex(0),
    deadGhostCount(0),
    mtx(std::make_unique<std::mutex>()),
    ghostEaten(ghostEaten)
{
    pacman = std::make_shared<Pacman>();
    blinky = std::make_shared<Blinky>();
    pinky = std::make_shared<Pinky>();
    inky = std::make_shared<Inky>();
    clyde = std::make_shared<Clyde>();
    
    releaseOrder = {pinky, inky, clyde};

    std::function<void()> hideGhost = [this]()
    {
        this->hideGhostHandler();
    };
    this->timer = std::make_unique<Timer>(0, 0, hideGhost, 1.0);
    this->timerThread = std::make_unique<std::thread>(&Timer::run, this->timer.get());
}

CharacterManager::~CharacterManager()
{    
    if (this->timerThread != nullptr)
    {
        this->timer->stop();
        this->timerThread->join();
        this->timerThread.reset();
    }
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
    checkCollision();
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

        if (nextStepDirection == Direction::NONE)
        {
            ghost->addNextDirection(Direction::LEFT);
            ghost->setExiting(false);
            ghost->setHome(false);
            return true;
        }

        if (Cell{x, y} == nextStepCell)
        {
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

    selectNewDirection(adjacentTile, legalDirections, ghost);

    bool onTrackX = (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) && ((y + 4) % 8 == 0);
    bool onTrackY = (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) && ((x + 4) % 8 == 0);

    if (onTrackX || onTrackY)
    {
        Direction changedDirection = ghost->getNextDirection();
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
        switch (ghost->getMode())
        {
            case GhostMode::SCATTER:
            {
                Cell targetCell = ghost->getTarget();
                findNextDirection(targetCell, adjacentTile, legalDirections, newDirection);
            }
            break;
            case GhostMode::CHASE:
            {
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

    if (ghostMode == GhostMode::FRIGHTENED)
    {
        deadGhostCount = 0;
    }

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

void CharacterManager::checkCollision()
{
    for (std::shared_ptr<Ghost> ghost : getGhosts())
    {
        Cell ghostTile = Util::getCenter(ghost->getX(), ghost->getY());
        Cell pacmanTile = Util::getCenter(pacman->getX(), pacman->getY());

        if (ghostTile == pacmanTile)
        {
            printf("Collision between Pacman and %s!\n", typeid(*ghost).name());
            if (ghost->getMode() == GhostMode::FRIGHTENED)
            {
                deadGhostCount++;
                printf("Pacman ate %s\n", typeid(*ghost).name());
                ghost->hide();
                pacman->hide();
                ghost->setMode(GhostMode::EYES);
                this->ghostEaten(deadGhostCount, ghostTile, ghost);
            }
            else if (ghost->getMode() == GhostMode::CHASE || ghost->getMode() == GhostMode::SCATTER)
            {
                printf("Pacman died by the hand of %s\n", typeid(*ghost).name());
                freezeCharacters();
                this->timer->startTimer();
            }
        }
    }
}

void CharacterManager::freezeCharacters()
{
    mtx->lock();

    pacman->setCollided();
    blinky->setCollided();
    pinky->setCollided();
    inky->setCollided();
    clyde->setCollided();

    mtx->unlock();
}

void CharacterManager::hideCharacters()
{
    mtx->lock();

    //pacman->hide();
    blinky->hide();
    pinky->hide();
    inky->hide();
    clyde->hide();

    mtx->unlock();
}

void CharacterManager::hideGhostHandler()
{
    hideCharacters();
}

}

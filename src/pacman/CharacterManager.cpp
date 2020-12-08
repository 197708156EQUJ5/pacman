#include "pacman/CharacterManager.hpp"

#include "pacman/Level.hpp"
#include "pacman/GhostMode.hpp"
#include "pacman/Utils.hpp"

#include <bits/stdc++.h>
#include <algorithm>
#include <typeinfo>
#include <iomanip>

namespace pacman
{
    
CharacterManager::CharacterManager()
{
    pacman = std::make_shared<Pacman>();
    blinky = std::make_shared<Blinky>();
    pinky = std::make_shared<Pinky>();
    inky = std::make_shared<Inky>();
    clyde = std::make_shared<Clyde>();
}

std::shared_ptr<Pacman> CharacterManager::getPacman()
{
    return pacman;
}

std::vector<std::shared_ptr<Ghost>> CharacterManager::getGhosts()
{
    std::vector<std::shared_ptr<Ghost>> ghost{pinky, inky, blinky, clyde};
    return ghost;
}

bool CharacterManager::canMovePacman()
{
    int x = pacman->getX();
    int y = pacman->getY();
    Direction direction = pacman->getDirection();
    AdjacentTile adjacentTile = Util::getAdjacentTiles(x, y, direction);
    
    //return Level::isLegalMove(Cell{next.col / Constants::TILE_SIZE, 
    //        (next.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE});
    return false;
}

bool CharacterManager::canMoveGhost(std::shared_ptr<Ghost> ghost)
{
    int x = ghost->getX();
    int y = ghost->getY();
    Direction ghostDirection = ghost->getDirection();

    //Util::displayGhost<Pinky>(ghost);
    if (ghost->isHome()&& !ghost->isExiting())
    {
        AdjacentTile homeAdjacentTile = Util::getAdjacentTiles(x, y, ghostDirection);
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
        std::pair<Cell, Direction> nextStep = ghost->peekNextExitStep();
        Cell nextStepCell = nextStep.first;
        Direction nextStepDirection = nextStep.second;

        if (nextStepDirection == Direction::NONE)
        {
            ghost->addNextDirection(Direction::LEFT);
            ghost->setExiting();
            ghost->setHome();
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
        adjacentTile = Util::getAdjacentTiles(x, y, ghostDirection);
    }
    else
    {
        adjacentTile = Util::getAdjacentTiles(x, y, peekDirection);
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
        printf("GhostMode[%s]: %d\n", typeid(*ghost).name(), ghost->getMode());
        switch (ghost->getMode())
        {
            case GhostMode::SCATTER:
            {
                if (typeid(*ghost) == typeid(Pinky))
                {
                    printf("SCATTER %s", typeid(*ghost).name());
                }
                float shorterDistance = 10000000.0;
                int shorterDirection = INT_MAX;
                for (int d : legalDirections)
                {
                    Cell current = adjacentTile.fromDirection((Direction)d);
                    Cell target = ghost->getTarget();
                    float distance = Util::distance(current.col, current.row, target.col, target.row);
                    if (typeid(*ghost) == typeid(Pinky))
                    {
                        printf("\ndir: %d curr (%3d, %3d) target (%3d, %3d) distance: %.3f ", d, current.col, current.row, target.col, target.row, distance);
                    }
                    if (distance < shorterDistance || (distance == shorterDistance && d < shorterDirection))
                    {
                        shorterDistance = distance;
                        shorterDirection = d;
                        newDirection = (Direction) d;
                    }
                }
                if (typeid(*ghost) == typeid(Pinky))
                {
                    printf("next direction; %d\n", newDirection);
                }
            }
            break;
            case GhostMode::CHASE:
            {
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

}

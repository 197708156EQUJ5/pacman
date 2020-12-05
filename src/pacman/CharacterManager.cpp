#include "pacman/CharacterManager.hpp"

#include "pacman/Level.hpp"
#include "pacman/Utils.hpp"

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
    /*
    if (typeid(*ghost) == typeid(Blinky))
    {
        printf("Blinky x, y: (%3d, %3d) direction: %d next: %d\n", x, y, (int)ghostDirection, (int)ghost->peekNextDirection());
    }
    */
    Util::displayGhost<Blinky>(ghost);
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
    Util::displayTiles<Blinky>(adjacentTile, ghost);
    ghost->setCurrentTile(Util::getCurrentCell(x, y));

    std::vector<int> legalDirections = findLegalDirections(adjacentTile, ghost);

    if (typeid(*ghost) == typeid(Blinky))
    {
        printf("(%3d, %3d) {", x, y);
        for (int dir : legalDirections)
        {
            printf("%d ", dir);
        }
        printf("}\n");
    }

    std::vector<int>::iterator itDirection;
    /*
    if (ghost->isHome())
    {
        itDirection = find(legalDirections.begin(), legalDirections.end(), (int)ghostDirection);
        if (typeid(*ghost) == typeid(Pinky))
        {
            //ss << "} COUNT: " << legalDirections.size();
            //ss << " direction: [" << (int)ghostDirection << "]";
            //std::cout << ss.str() << std::endl;
        }
        if (itDirection != legalDirections.end())
        {
            ghost->changeDirection(ghostDirection);
            return true;
        }
        ghost->changeDirection(Util::getOpposite(ghostDirection));
        return true;
    }
    */
    Direction newDirection = Direction::NONE;
    if (legalDirections.size() == 1 && ghost->hasTileChanged())
    {
        newDirection = (Direction)legalDirections.at(0);
        ghost->addNextDirection(newDirection);
        if (typeid(*ghost) == typeid(Blinky))
        {
            printf("legal size: %d, tileChanged adding next direction; %d\n", legalDirections.size(), newDirection);
        }
    }

    if (legalDirections.size() > 1 && ghost->hasTileChanged())
    {
        newDirection = (Direction)(legalDirections.at(std::rand() % legalDirections.size()));
        ghost->addNextDirection(newDirection);
        if (typeid(*ghost) == typeid(Blinky))
        {
            printf("legal size: %d, tileChanged adding next direction; %d\n", legalDirections.size(), newDirection);
        }
    }
    
    bool onTrackX = (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) && ((y + 4) % 8 == 0);
    bool onTrackY = (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) && ((x + 4) % 8 == 0);

    if (onTrackX || onTrackY)
    {
        Direction changedDirection = ghost->getNextDirection();
        if (typeid(*ghost) == typeid(Blinky))
        {
            printf("changing direction; %d\n", changedDirection);
        }
        ghost->changeDirection(changedDirection);
    }
    if (typeid(*ghost) == typeid(Pinky))
    {
        //ss << "} COUNT: " << legalDirections.size();
        //ss << " x: " << x << " U/D? " << (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) << " % 8 == 0? " << (((y + 4) % 8) == 0);
        //ss << " y: " << y << " L/R? " << (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) << " % 8 == 0? " << (((x + 4) % 8) == 0);
        //ss << " direction: [" << (int)ghostDirection << ":" << (int)newDirection << "]";
        //ss << " onTrack X? " << std::boolalpha << onTrackX << " Y? " << std::boolalpha << onTrackY;
        //std::cout << ss.str() << std::endl;
    }

    return true;
}

std::vector<int> CharacterManager::findLegalDirections(AdjacentTile adjacentTile, std::shared_ptr<Ghost> ghost)
{
    int directionIndex = 1;
    std::vector<int> legalDirections;
    
    for (Cell cell : adjacentTile.tiles)
    {
        if ((Level::isLegalMove(Util::convertToGrid(cell)) ||
                (ghost->isExiting() && Level::getCellType(Util::convertToGrid(cell)) == Level::GHOST_HOUSE_DOOR)) &&
                (Util::getCenter(cell) != ghost->getCurrentTile()))
        {
            legalDirections.push_back(directionIndex);
        }
        directionIndex++;
    }

    return legalDirections;
}

}

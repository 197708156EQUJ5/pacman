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
    if (typeid(*ghost) == typeid(Blinky))
    {
        printf("Blinky x, y: (%3d, %3d) direction: %d next: %d\n", x, y, (int)ghostDirection, (int)ghost->peekNextDirection());
    }
    AdjacentTile adjacentTile = Util::getAdjacentTiles(x, y, ghost->peekNextDirection());
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
    }

    if (legalDirections.size() > 1 && ghost->hasTileChanged())
    {
        newDirection = (Direction)(legalDirections.at(std::rand() % legalDirections.size()));
        ghost->addNextDirection(newDirection);
    }
    
    bool onTrackX = (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) && ((y + 4) % 8 == 0);
    bool onTrackY = (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) && ((x + 4) % 8 == 0);

    if (onTrackX || onTrackY)
    {
        ghost->changeDirection(ghost->getNextDirection());
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
    std::vector<Cell>::iterator it = adjacentTile.tiles.begin();
    int directionIndex = 1;
    std::vector<int> legalDirections;
    
    for (it; it != adjacentTile.tiles.end(); ++it)
    {
        Cell cell = *it;
        if (typeid(*ghost) == typeid(Blinky))
        {
            /*
            Cell cell1 = Util::getCenter(cell);
            Cell cell1Grid = Util::convertToGrid(cell1);
            Cell cell2 = ghost->getCurrentTile();
            Cell cellType = Level::getCellType(Util::convertToGrid(cell));
            Cell current = Util::getCenter(ghost->getCurrentTile());
            Cell cellDoor = Level::GHOST_HOUSE_DOOR;
            printf("cell1 (%3d, %3d:%3d, %3d {%2d, %2d}) cell2 (%3d, %3d) curr (%3d, %3d) DOOR: {%2d, %2d}\n", 
                    cell1.col, cell1.row, 
                    cell1Grid.col, cell1Grid.row, 
                    cellType.col, cellType.row, 
                    cell2.col, cell2.row,
                    current.col, current.row,
                    cellDoor.col, cellDoor.row);
            */
        }
        if ((Level::isLegalMove(Util::convertToGrid(cell)) ||
                (ghost->isExiting() && Level::getCellType(Util::convertToGrid(cell)) == Level::GHOST_HOUSE_DOOR)) &&
                (Util::getCenter(cell) != ghost->getCurrentTile()))
        //if (Level::isLegalMove(Util::convertToGrid(cell)) && cell != adjacentTile.current && (ghost->isExiting() && cell == Level::GHOST_HOUSE_DOOR))
        {
            legalDirections.push_back(directionIndex);
        }
        directionIndex++;
    }

    return legalDirections;
}

void CharacterManager::printCells(AdjacentTile adjacentTile, std::shared_ptr<Character> character)
{
    //if (typeid(*character) == typeid(Pacman))
    if (typeid(*character) == typeid(Pinky))
    {
        Cell northCT = Level::getCellType(adjacentTile.north.col / Constants::TILE_SIZE, (adjacentTile.north.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell eastCT = Level::getCellType(adjacentTile.east.col / Constants::TILE_SIZE, (adjacentTile.east.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell southCT = Level::getCellType(adjacentTile.south.col / Constants::TILE_SIZE, (adjacentTile.south.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell westCT = Level::getCellType(adjacentTile.west.col / Constants::TILE_SIZE, (adjacentTile.west.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        /*
        std::cout << "cr (" << std::setw(3) << (adjacentTile.north.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.west.row / Constants::TILE_SIZE) << ") "
            << "nx (" << std::setw(3) << (adjacentTile.next.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.next.row / Constants::TILE_SIZE) << ") "
            << "pv (" << std::setw(3) << (adjacentTile.prev.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.prev.row / Constants::TILE_SIZE) << ") "
            << "N (" << std::setw(3) << (adjacentTile.north.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.north.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << northCT.col << ", " << std::setw(2) << northCT.row << ") "
            << "E (" << std::setw(3) << (adjacentTile.east.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.east.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << eastCT.col << ", " << std::setw(2) << eastCT.row << ") "
            << "S (" << std::setw(3) << (adjacentTile.south.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.south.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << southCT.col << ", " << std::setw(2) << southCT.row << ") "
            << "W (" << std::setw(3) << (adjacentTile.west.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.west.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << westCT.col << ", " << std::setw(2) << westCT.row << ") " << std::endl;
        */
        std::cout << "cr (" << std::setw(3) << adjacentTile.north.col << ", " << std::setw(3) << adjacentTile.west.row << ") "
            //<< "nx (" << std::setw(3) << adjacentTile.next.col << ", " << std::setw(3) << adjacentTile.next.row << ") "
            //<< "pv: (" << std::setw(3) << adjacentTile.prev.col << ", " << std::setw(3) << adjacentTile.prev.row << ") "
            << "N (" << std::setw(3) << adjacentTile.north.col << ", " << std::setw(3) << adjacentTile.north.row << ") "
            << "E (" << std::setw(3) << adjacentTile.east.col << ", " << std::setw(3) << adjacentTile.east.row << ") "
            << "S (" << std::setw(3) << adjacentTile.south.col << ", " << std::setw(3) << adjacentTile.south.row << ") "
            << "W (" << std::setw(3) << adjacentTile.west.col << ", " << std::setw(3) << adjacentTile.west.row << ") "
            << std::endl;
    }
}

}

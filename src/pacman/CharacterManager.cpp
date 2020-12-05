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
    
    printCells(Level::getAdjacentTiles(x, y, direction), pacman);
    
    Cell next = Level::getAdjacentTiles(x, y, direction).next;
    return Level::isLegalMove(Cell{next.col / Constants::TILE_SIZE, 
            (next.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE});
}

bool CharacterManager::canMoveGhost(std::shared_ptr<Ghost> ghost)
{
    int x = ghost->getX();
    int y = ghost->getY();

    Direction ghostDirection = ghost->getDirection();
    AdjacentTile adjacentTile = Level::getAdjacentTiles(x, y, ghostDirection);

    std::stringstream ss;
    ss << "Legal direction: {";
    std::vector<Cell>::iterator it = adjacentTile.tiles.begin();
    int directionIndex = 1;
    Cell prevCell = adjacentTile.prev;
    std::vector<int> legalDirections;
    printCells(adjacentTile, ghost);
    
    for (it; it != adjacentTile.tiles.end(); ++it)
    {
        Cell cell = *it;
        if (Level::isGhostHouseDoor(convertToGridSpace(cell)) && ghostDirection == Direction::UP)
        {
            ss << " isGhostHouseDoor && UP ";
            legalDirections.push_back(directionIndex);
            ghost->setHome();
            break;
        }
        if (Level::isLegalMove(convertToGridSpace(cell)) && cell != prevCell)
        {
            ss << directionIndex << " ";
            legalDirections.push_back(directionIndex);
        }
        directionIndex++;
    }
    std::vector<int>::iterator itDirection;
    if (ghost->isHome())
    {
        itDirection = find(legalDirections.begin(), legalDirections.end(), (int)ghostDirection);
        if (typeid(*ghost) == typeid(Pinky))
        {
            ss << "} COUNT: " << legalDirections.size();
            ss << " direction: [" << (int)ghostDirection << "]";
            std::cout << ss.str() << std::endl;
        }
        if (itDirection != legalDirections.end())
        {
            ghost->changeDirection(ghostDirection);
            return true;
        }
        ghost->changeDirection(pacman::getOpposite(ghostDirection));
        return true;
    }

    Direction newDirection = Direction::NONE;
    if (legalDirections.size() == 1)
    {
        newDirection = (Direction)legalDirections.at(0);
    }

    if (legalDirections.size() > 1)
    {
        newDirection = (Direction)(legalDirections.at(std::rand() % legalDirections.size()));
    }
    
    bool onTrackX = (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) && ((y + 4) % 8 == 0);
    bool onTrackY = (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) && ((x + 4) % 8 == 0);

    if (onTrackX || onTrackY)
    {
        ghost->changeDirection(newDirection);
    }
    if (typeid(*ghost) == typeid(Pinky))
    {
        ss << "} COUNT: " << legalDirections.size();
        //ss << " x: " << x << " U/D? " << (ghostDirection == Direction::UP || ghostDirection == Direction::DOWN) << " % 8 == 0? " << (((y + 4) % 8) == 0);
        //ss << " y: " << y << " L/R? " << (ghostDirection == Direction::LEFT || ghostDirection == Direction::RIGHT) << " % 8 == 0? " << (((x + 4) % 8) == 0);
        ss << " direction: [" << (int)ghostDirection << ":" << (int)newDirection << "]";
        ss << " onTrack X? " << std::boolalpha << onTrackX << " Y? " << std::boolalpha << onTrackY;
        std::cout << ss.str() << std::endl;
    }

    return true;
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
            << "nx (" << std::setw(3) << adjacentTile.next.col << ", " << std::setw(3) << adjacentTile.next.row << ") "
            << "pv: (" << std::setw(3) << adjacentTile.prev.col << ", " << std::setw(3) << adjacentTile.prev.row << ") "
            << "N (" << std::setw(3) << adjacentTile.north.col << ", " << std::setw(3) << adjacentTile.north.row << ") "
            << "E (" << std::setw(3) << adjacentTile.east.col << ", " << std::setw(3) << adjacentTile.east.row << ") "
            << "S (" << std::setw(3) << adjacentTile.south.col << ", " << std::setw(3) << adjacentTile.south.row << ") "
            << "W (" << std::setw(3) << adjacentTile.west.col << ", " << std::setw(3) << adjacentTile.west.row << ") "
            << std::endl;
    }
}

}

#include "pacman/Board.hpp"

#include "pacman/Constants.hpp"

#include <typeinfo>
#include <cstdlib>
#include <iomanip>

namespace pacman
{
Board::Board() :
    userDirection(Direction::LEFT),
    score(0),
    lives(2),
    level(1),
    count(0)
{
}

Board::~Board()
{
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Board::init()
{
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
            Constants::BOARD_WIDTH, Constants::BOARD_HEIGHT, 0);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return false;
    }

    surface = SDL_GetWindowSurface(window);

    if (!surface)
    {
        std::cout << "Failed to get window's surface\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return false;
    }

    spriteSheet = std::make_unique<SpriteSheet>();
    characterManager = std::make_unique<CharacterManager>();
    maze = Level::LEVEL_1;
    //maze = Level::getLevel();
    pacman = this->characterManager->getPacman();
    ghosts = characterManager->getGhosts();
    gameStartTime = std::chrono::system_clock::now();

    return true;
}

void Board::setUserDirection(Direction direction)
{
    userDirection = direction;
}

void Board::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    drawBoard();
    drawScore();
    
    drawPacman();
    
    drawGhosts();


    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - gameStartTime);
    if (duration.count() > 1000)
    {
        updatePacman();
        updateGhosts();
        count++;
    }

    //SDL_Delay(33.333333);
    //SDL_Delay(300);
    SDL_Delay(16.6666667);
    SDL_UpdateWindowSurface(window);
}

void Board::drawBoard()
{
    drawText();
    drawMaze();
}

void Board::drawText()
{
    std::vector<Cell> highScoreText{Constants::H, Constants::I, Constants::G, Constants::H, Cell{30, 5}, 
        Constants::S, Constants::C, Constants::O, Constants::R, Constants::E};
    for (int i = 0; i < highScoreText.size(); i++)
    {
        SDL_Rect position = {(i + 9) * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 0 * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)};
        Cell text = highScoreText.at(i);
        spriteSheet->selectSprite(text.col, text.row);
        spriteSheet->drawSelectedSprite(surface, &position);
    }
}

void Board::drawMaze()
{
    int colCount = 0;
    int rowCount = 3;

    // TODO Potential memory leak
    maze = Level::getLevel();
    for (Cell cell : maze)
    {
        SDL_Rect position = {colCount * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), rowCount * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)};
        if (cell.hasVisited)
        {
            spriteSheet->selectSprite(Constants::EMPTY.col, Constants::EMPTY.row);
        }
        else
        {
            spriteSheet->selectSprite(cell.col, cell.row);
        }
        spriteSheet->drawSelectedSprite(surface, &position);
        colCount++;
        if (colCount % Constants::COLUMN_COUNT == 0)
        {
            colCount = 0;
            rowCount++;
        }
    }
}

void Board::drawScore()
{
    int col = 6;
    int local_score = score;

    for (int i = 1; i <= 1000000; i *= 10)
    {
        int digit = local_score % 10;
        local_score = local_score / 10;
        SDL_Rect position = {col * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 1 * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)};
        spriteSheet->selectSprite(digit, Constants::NUM_ROW);
        spriteSheet->drawSelectedSprite(surface, &position);
        col--;
    }
}

void Board::drawLives()
{
}

void Board::drawFruits()
{
}

void Board::drawPacman()
{
    drawCharacter(pacman);
}

void Board::updatePacman()
{
    if (canMovePacman())
    {
        pacman->move();
        //score += Level::getCellValue(getCharacterCenter(pacman));
    }
    pacman->changeDirection(userDirection);
}

bool Board::canMovePacman()
{
    int x = pacman->getX();
    int y = pacman->getY();
    Direction direction = pacman->getDirection();
    
    //printCells(Level::getAdjacentTiles(x, y, direction), pacman);
    
    Cell next = Level::getAdjacentTiles(x, y, direction).next;
    return Level::isLegalMove(Cell{next.col / Constants::TILE_SIZE, 
            (next.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE});
}

void Board::drawGhosts()
{
    for (std::shared_ptr<Ghost> ghost : ghosts)
    {
        drawCharacter(ghost);
    }
}

void Board::drawCharacter(std::shared_ptr<Character> character)
{
    int i = 1;
    int j = 1;
    for (int srcRow = 0; srcRow < 2; srcRow++)
    {
        for (int srcCol = 0; srcCol < 2; srcCol++)
        {
            int x = (character->getX() * Constants::TILE_DISPLAY_RATIO) - (i * Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO);
            int y = (character->getY() * Constants::TILE_DISPLAY_RATIO) - (j * Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO);
            int width = Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO;
            int height = Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO;

            SDL_Rect position = {x, y, width, height};
            spriteSheet->selectSprite(character->getSrcCol() + srcCol, character->getSrcRow() + srcRow);
            spriteSheet->drawSelectedSprite(surface, &position);
            i--;
        }
        i = 1;
        j--;
    }
}

void Board::updateGhosts()
{
    for (std::shared_ptr<Ghost> ghost : ghosts)
    {
        if (canMoveGhost(ghost))
        {
            ghost->move();
        }
    }
}

bool Board::canMoveGhost(std::shared_ptr<Ghost> ghost)
{
    int x = ghost->getX();
    int y = ghost->getY();
    Direction direction = ghost->getDirection();
    AdjacentTile adjacentTile = Level::getAdjacentTiles(x, y, direction);
    

    Direction ghostDirection = ghost->getDirection();
    if (ghost->isHome())
    {
        ghost->changeDirection(pacman::getOpposite(ghostDirection));
        return true;
    }
    std::vector<Cell>::iterator it = adjacentTile.tiles.begin();
    int directionIndex = 1;
    Cell prevCell = adjacentTile.prev;
    std::vector<Direction> legalDirections;
    //printCells(adjacentTile, ghost);

    for (it; it != adjacentTile.tiles.end(); ++it)
    {
        Cell cell = *it;
        if (Level::isGhostHouseDoor(convertToGridSpace(cell)) && ghostDirection == Direction::UP)
        {
            legalDirections.push_back((Direction)directionIndex);
            break;
        }
        if (Level::isLegalMove(convertToGridSpace(cell)) && cell != prevCell)
        {
            //printf("Adding direction: %d\n", directionIndex);
            legalDirections.push_back((Direction)directionIndex);
        }
        directionIndex++;
    }

    Direction newDirection = Direction::NONE;
    //printf("legalDirection count: %d\n", legalDirections.size());
    if (legalDirections.size() == 1)
    {
        newDirection = legalDirections.at(0);
    }

    if (legalDirections.size() > 1)
    {
        newDirection = (Direction)(legalDirections.at(std::rand() % legalDirections.size()));
        //Cell prevCellType = maze.at(prevCell.row * Constants::COLUMN_COUNT + prevCell.col);
        /*
        if (typeid(*ghost) == typeid(Blinky))
        {
            printf("cell[%d] (%2d, %2d) prevCell (%2d, %2d) type (%2d, %2d) (%2d, %2d)\n", directionIndex, cell.col, cell.row, prevCell.col, prevCell.row,
                    cellType.col, cellType.row, prevCellType.col, prevCellType.row);
            printf("canMove? %d cells don't equal? %d\n", Level::canMove(cellType), !(cell == prevCell));
        }
        */
    }
    //printf("new direction: %d\n", newDirection);
    ghost->changeDirection(newDirection);
    //printf("ghost direction: %d\n", ghost->getDirection());
    return true;
}

Cell Board::convertToGridSpace(const Cell& cell)
{
    return Cell{cell.col / Constants::TILE_SIZE, (cell.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE};

}

void Board::printCells(AdjacentTile adjacentTile, std::shared_ptr<Character> character)
{
    //if (typeid(*character) == typeid(Pacman))
    if (typeid(*character) == typeid(Blinky))
    {
        Cell northCT = Level::getCellType(adjacentTile.north.col / Constants::TILE_SIZE, (adjacentTile.north.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell eastCT = Level::getCellType(adjacentTile.east.col / Constants::TILE_SIZE, (adjacentTile.east.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell southCT = Level::getCellType(adjacentTile.south.col / Constants::TILE_SIZE, (adjacentTile.south.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        Cell westCT = Level::getCellType(adjacentTile.west.col / Constants::TILE_SIZE, (adjacentTile.west.row - Constants::TOP_ROW_OFFSET) / Constants::TILE_SIZE);
        std::cout << "cr (" << std::setw(3) << (adjacentTile.north.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.west.row / Constants::TILE_SIZE) << ") "
            << "nx (" << std::setw(3) << (adjacentTile.next.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.next.row / Constants::TILE_SIZE) << ") "
            << "pv: (" << std::setw(3) << (adjacentTile.prev.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.prev.row / Constants::TILE_SIZE) << ":"
            << "N (" << std::setw(3) << (adjacentTile.north.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.north.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << northCT.col << ", " << std::setw(2) << northCT.row << ") "
            << "E (" << std::setw(3) << (adjacentTile.east.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.east.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << eastCT.col << ", " << std::setw(2) << eastCT.row << ") "
            << "S (" << std::setw(3) << (adjacentTile.south.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.south.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << southCT.col << ", " << std::setw(2) << southCT.row << ") "
            << "W (" << std::setw(3) << (adjacentTile.west.col / Constants::TILE_SIZE) << ", " << std::setw(3) << (adjacentTile.west.row / Constants::TILE_SIZE) << ":"
            << std::setw(2) << westCT.col << ", " << std::setw(2) << westCT.row << ") " << std::endl;
    }
}

} // namespace

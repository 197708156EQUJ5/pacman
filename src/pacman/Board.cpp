#include "pacman/Board.hpp"

#include "pacman/Constants.hpp"

#include <typeinfo>
#include <algorithm>

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
    maze = LevelDesign::LEVEL_1;
    legalTiles = LevelDesign::LEGAL_TILES;
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
    if (duration.count() > 3000)
    {
        updatePacman();
        updateGhosts();
        count++;
    }

    SDL_Delay(33.333);
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
    for (int i = 0; i < 10; i++)
    {
        SDL_Rect position = {(i + 9) * Constants::CHARACTER_SIZE, 0 * Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
        Cell text = highScoreText.at(i);
        spriteSheet->selectSprite(text.col, text.row);
        spriteSheet->drawSelectedSprite(surface, &position);
    }
}

void Board::drawMaze()
{
    int colCount = 0;
    int rowCount = 3;

    for (Cell cell : maze)
    {
        SDL_Rect position = {colCount * Constants::CHARACTER_SIZE, rowCount * Constants::CHARACTER_SIZE, 
            Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
        spriteSheet->selectSprite(cell.col, cell.row);
        spriteSheet->drawSelectedSprite(surface, &position);
        colCount++;
        if (colCount % Constants::COLUMN_COUNT == 0 )
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
        SDL_Rect position = {col * Constants::CHARACTER_SIZE, 1 * Constants::CHARACTER_SIZE, 
            Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
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
    }
    pacman->changeDirection(userDirection);
}

bool Board::canMovePacman()
{
    return canMove(getAdjacentTiles(pacman).nextTile);
}

bool Board::canChangeDirection()
{
    if (pacman->getX() % Constants::CHARACTER_SIZE == 0|| pacman->getY() % Constants::CHARACTER_SIZE == 0)
    {
        return false;
    }    
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
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_Rect position = {character->getX() + (i * Constants::CHARACTER_SIZE),
                character->getY() + (j * Constants::CHARACTER_SIZE) - (Constants::CHARACTER_SIZE / 2),
                Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
            spriteSheet->selectSprite(character->getSrcCol() + i, character->getSrcRow() + j);
            spriteSheet->drawSelectedSprite(surface, &position);
        }
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
    AdjacentTile adjacentTile = getAdjacentTiles(ghost);
    
    bool hasNextMove = canMove(adjacentTile.nextTile);
    if (!hasNextMove)
    {
        if (ghost->isHome())
        {
            ghost->changeDirection(pacman::getOpposite(ghost->getDirection()));
            return true;
        }
        std::vector<Cell>::iterator it = adjacentTile.tiles.begin();
        int directionIndex = 1;
        Cell prevCell = adjacentTile.prevTile;
        for (it; it != adjacentTile.tiles.end(); ++it)
        {
            Cell cell = *it;
            
            //Cell prevCellType = maze.at(prevCell.row * Constants::COLUMN_COUNT + prevCell.col);
            /*
            if (typeid(*ghost) == typeid(Blinky))
            {
                printf("cell[%d] (%2d, %2d) prevCell (%2d, %2d) type (%2d, %2d) (%2d, %2d)\n", directionIndex, cell.col, cell.row, prevCell.col, prevCell.row,
                        cellType.col, cellType.row, prevCellType.col, prevCellType.row);
                printf("canMove? %d cells don't equal? %d\n", canMove(cellType), !(cell == prevCell));
            }
            */
            if (canMove(cell) && cell != prevCell)
            {
                ghost->changeDirection((Direction)directionIndex);
                //printf("ghost direction: %d\n", ghost->getDirection());
                return true;
            }
            directionIndex++;
        }
    }

    return hasNextMove;
}

AdjacentTile Board::getAdjacentTiles(std::shared_ptr<Character> character)
{
    int centerX = character->getX() + Constants::CHARACTER_SIZE;
    int centerY = character->getY() + Constants::CHARACTER_SIZE - (Constants::MAZE_ROW_OFFSET * Constants::CHARACTER_SIZE);
    Direction direction = character->getDirection();
    
    int row = centerY / Constants::CHARACTER_SIZE;
    int col = centerX / Constants::CHARACTER_SIZE;

    /*
    if (typeid(*character) == typeid(Blinky))
    {
        printf("Blinky col, row (%2d, %2d)\n", col, row);
    }
    */

    int nextRow = row;
    int nextCol = col;
    int prevRow = row;
    int prevCol = col;
    if (direction == Direction::LEFT)
    {
        nextCol--;
        prevCol++;
    }
    else if (direction == Direction::RIGHT)
    {
        nextCol++;
        prevCol--;
    }
    else if (direction == Direction::UP)
    {
        nextRow--;
        prevRow++;
    }
    else if (direction == Direction::DOWN)
    {
        nextRow++;
        prevRow--;
    }

    return {Cell{nextCol, nextRow}, Cell{prevCol, prevRow}, Cell{col, row - 1}, Cell{col + 1, row}, Cell{col, row + 1}, Cell{col - 1, row}};
}

bool Board::canMove(Cell cell)
{

    //if (typeid(*character) == typeid(Clyde))
    //{
    //    printf("cell_src col/row: (%2d, %2d) next_src col/row: (%2d, %2d) curr_index (%2d, %2d) next_index COL/ROW (%2d, %2d)\n", 
    //            cell.col, cell.row, nextCell.col, nextCell.row, col, row, nextCol, nextRow);
    //}
    //printf("Cell (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d)\n", 
    //        cell.col, cell.row, nextCell.col, nextCell.row, nextCol, nextRow, col, row, centerX, centerY);
    if (find (legalTiles.begin(), legalTiles.end(), LevelDesign::getCellType(cell.col, cell.row)) == legalTiles.end())
    {
        return false;
    }

    return true;
}

} // namespace

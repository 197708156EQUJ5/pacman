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
        if (digit == 0)
        {
            spriteSheet->selectSprite(Constants::NUM_COL_0, Constants::NUM_ROW);
        }
        else if (digit == 1)
        {
            spriteSheet->selectSprite(Constants::NUM_COL_1, Constants::NUM_ROW);
        }
        else if (digit == 2)
        {
            spriteSheet->selectSprite(Constants::NUM_COL_2, Constants::NUM_ROW);
        }
        else if (digit == 3)
        {
            spriteSheet->selectSprite(Constants::NUM_COL_3, Constants::NUM_ROW);
        }
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
    return canMove(pacman);
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
    return canMove(ghost);
}

bool Board::canMove(std::shared_ptr<Character> character)
{
    int centerX = character->getX() + Constants::CHARACTER_SIZE;
    int centerY = character->getY() + Constants::CHARACTER_SIZE - (4 * Constants::CHARACTER_SIZE);
    Direction direction = character->getDirection();

    //printf("left-corner: (%d, %d) center: (%d, %d) maze size: %d\n", 
    //       character->getX(), character->getY(), centerX, centerY, maze.size());

    int row = centerY / Constants::CHARACTER_SIZE;
    int col = centerX / Constants::CHARACTER_SIZE;
    int nextRow = row;
    int nextCol = col;
    if (direction == Direction::LEFT)
    {
        nextCol--;
    }
    else if (direction == Direction::RIGHT)
    {
        nextCol++;
    }
    else if (direction == Direction::UP)
    {
        nextRow--;
    }
    else if (direction == Direction::DOWN)
    {
        nextRow++;
    }

    Cell cell = maze.at(((centerY / Constants::CHARACTER_SIZE) * Constants::COLUMN_COUNT) + (centerX/ Constants::CHARACTER_SIZE));
    Cell nextCell = maze.at(nextRow * Constants::COLUMN_COUNT + nextCol);

    //if (typeid(*character) == typeid(Blinky))
    //{
    //    printf("cell col/row: (%3d, %3d) next col/row: (%3d, %3d)\n", 
    //            cell.col, cell.row, nextCell.col, nextCell.row);
    //}
    //printf("Cell (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d)\n", 
    //        cell.col, cell.row, nextCell.col, nextCell.row, nextCol, nextRow, col, row, centerX, centerY);
    if (find (legalTiles.begin(), legalTiles.end(), nextCell) == legalTiles.end())
    {
        return false;
    }

    return true;
}

} // namespace

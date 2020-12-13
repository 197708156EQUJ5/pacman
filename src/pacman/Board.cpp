#include "pacman/Board.hpp"

#include "pacman/Constants.hpp"
#include "pacman/Direction.hpp"
#include "pacman/Level.hpp"

#include <algorithm> 
#include <cstdlib>
#include <sstream>
#include <iostream>

using namespace std::chrono;
using namespace std;

namespace pacman
{

Board::Board() :
    userDirection(Direction::LEFT),    
    score(0),
    lives(2),
    level(0),
    frameCount(0),
    showFruit(false)
{
}

Board::~Board()
{

    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);

    SDL_Quit();
    
    if (this->ghostModeThread != nullptr)
    {
        this->ghostModeTimer->stop();
        this->ghostModeThread->join();
        this->ghostModeThread.reset();
    }
    
    if (this->fruitThread != nullptr)
    {
        this->fruitTimer->stop();
        this->fruitThread->join();
        this->fruitThread.reset();
    }
}

bool Board::init()
{
    //window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    window = SDL_CreateWindow("Pacman", 1240, 30,
            Constants::BOARD_WIDTH, Constants::BOARD_HEIGHT, SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        cout << "Failed to create window\n";
        cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return false;
    }

    surface = SDL_GetWindowSurface(window);

    if (!surface)
    {
        cout << "Failed to get window's surface\n";
        cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return false;
    }

    spriteSheet = make_unique<SpriteSheet>();
    characterManager = make_unique<CharacterManager>();
    fruitManager = make_unique<FruitManager>();

    maze = Level::LEVEL_1;
    //maze = Level::getLevel();
    pacman = this->characterManager->getPacman();
    ghosts = this->characterManager->getGhosts();
    gameStartTime = steady_clock::now();

    function<void(GhostMode)> transitionGhostMode = [this](GhostMode ghostMode)
    {
        this->transitionGhostModeHandler(ghostMode);
    };

    this->transitionDelays = {make_pair(0, GhostMode::SCATTER), make_pair(7, GhostMode::CHASE), 
        make_pair(20, GhostMode::SCATTER), make_pair(7, GhostMode::CHASE), 
        make_pair(20, GhostMode::SCATTER), make_pair(5, GhostMode::CHASE), 
        make_pair(20, GhostMode::SCATTER), make_pair(5, GhostMode::CHASE)};
    this->ghostModeTimer = make_unique<GhostModeTimer>(this->transitionDelays, transitionGhostMode);
    this->ghostModeThread = make_unique<thread>(&GhostModeTimer::run, this->ghostModeTimer.get());
    this->ghostModeTimer->startTimer();

    function<void()> removeFruit = [this]()
    {
        this->removeFruitHandler();
    };
    this->fruitTimer = make_unique<Timer>(9, 10, removeFruit);
    this->fruitThread = make_unique<thread>(&Timer::run, this->fruitTimer.get());

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
    drawFruits();
    drawLives();
    drawPacman();
    drawGhosts();

    milliseconds sinceGameStart = duration_cast<milliseconds>(steady_clock::now() - gameStartTime);
    frameCount++;
    /*
    if (frameCount % 30 == 0)
    {
        cout << "time: " << sinceGameStart.count() << endl;
    }
    */
    if (sinceGameStart.count() > Constants::LEVEL_START_DELAY)
    {
        updatePacman();
        updateGhosts();
    }

    //SDL_Delay(33.333333);
    //SDL_Delay(300);
    //SDL_Delay(16.6666667);
    SDL_UpdateWindowSurface(window);
}

void Board::drawBoard()
{
    drawText();
    drawMaze();
}

void Board::drawText()
{
    vector<Cell> highScoreText{Constants::H, Constants::I, Constants::G, Constants::H, Cell{30, 5}, 
        Constants::S, Constants::C, Constants::O, Constants::R, Constants::E};
    for (int i = 0; i < highScoreText.size(); i++)
    {
        SDL_Rect position = {(i + 9) * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            0 * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
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
        SDL_Rect position = {colCount * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            rowCount * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), 
            (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO), (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)};
        if (cell.hasVisited)
        {
            spriteSheet->selectSprite(Constants::EMPTY.col, Constants::EMPTY.row);
        }
        else
        {
            spriteSheet->selectSprite(cell.col, cell.row);
        }
        if (cell == Level::ENERGIZER && ((frameCount / 10) % 2 == 0))
        {
            spriteSheet->drawSelectedSprite(surface, &position);
        }
        else if (cell != Level::ENERGIZER)
        {
            spriteSheet->drawSelectedSprite(surface, &position);
        }
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
    for (int i = 0; i < lives; i++)
    {
        drawLargeTile(PacmanConstants::LIVES_START_COL + (i * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)),
                PacmanConstants::LIVES_START_ROW, PacmanConstants::SRC_LEFT_1, PacmanConstants::SRC_ROW);
    }
}

void Board::drawFruits()
{
    if (!showFruit && (pacman->getDotCounter() == PacmanConstants::FIRST_FRUIT || 
                pacman->getDotCounter() == PacmanConstants::SECOND_FRUIT))
    {
        showFruit = true;
    }

    if (showFruit)
    {
        int x = FruitConstants::COL;
        int y = FruitConstants::ROW;

        Cell fruitCell = fruitManager->getFruit(level);
        drawLargeTile(x, y, fruitCell.col, fruitCell.row);
        this->fruitTimer->startTimer();
    }

    for (int i = max(level - 7, 0); i <= level; i++)
    {
        Cell fruitCell = fruitManager->getFruit(i);
        drawLargeTile(FruitConstants::LEVEL_START_COL - (i * (Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO)),
                FruitConstants::LEVEL_START_ROW, fruitCell.col, fruitCell.row);
    }
}

void Board::drawPacman()
{
    drawCharacter(pacman);
}

void Board::drawGhosts()
{
    for (shared_ptr<Ghost> ghost : ghosts)
    {
        drawCharacter(ghost);
    }
}

void Board::drawCharacter(shared_ptr<Character> character)
{
    //printf("{drawCharacter} %s (%3d, %3d)\n", typeid(*character).name(), character->getX(), character->getY());

    if (!character->isHidden())
    {
        drawLargeTile(character->getX(), character->getY(), character->getSrcCol(), character->getSrcRow());
    }
}


void Board::drawLargeTile(int tileX, int tileY, int tileSrcCol, int tileSrcRow)
{
    int i = 1;
    int j = 1;
    for (int srcRow = 0; srcRow < 2; srcRow++)
    {
        for (int srcCol = 0; srcCol < 2; srcCol++)
        {
            int x = (tileX * Constants::TILE_DISPLAY_RATIO) - (i * Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO);
            int y = (tileY * Constants::TILE_DISPLAY_RATIO) - (j * Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO);
            int width = Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO;
            int height = Constants::TILE_SIZE * Constants::TILE_DISPLAY_RATIO;

            SDL_Rect position = {x, y, width, height};
            spriteSheet->selectSprite(tileSrcCol + srcCol, tileSrcRow + srcRow);
            spriteSheet->drawSelectedSprite(surface, &position);
            i--;
        }
        i = 1;
        j--;
    }
}

void Board::updatePacman()
{
    if (this->characterManager->canMovePacman())
    {
        pacman->move();
        int tileValue = Level::getCellValue(Util::convertToGrid(Cell{pacman->getX(), pacman->getY()}));
        if (tileValue > 0)
        {
            if (tileValue == Constants::ENERGIZER_VALUE)
            {
                characterManager->updateGhostMode(GhostMode::FRIGHTENED);
            }
            pacman->incrementDotCounter();
            characterManager->incrementDotCounter();
        }
        score += tileValue;
    }
    pacman->changeDirection(userDirection);
}

void Board::updateGhosts()
{
    for (shared_ptr<Ghost> ghost : ghosts)
    {
        if (this->characterManager->canMoveGhost(ghost))
        {
            ghost->move();
        }
    }
}

void Board::transitionGhostModeHandler(GhostMode ghostMode)
{
    printf("GhostMode: %d\n", ghostMode);
    characterManager->updateGhostMode(ghostMode);
}

void Board::removeFruitHandler()
{
    this->showFruit = false;
}

} // namespace

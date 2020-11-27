#include "pacman/Board.hpp"
#include "pacman/Constants.hpp"

namespace pacman
{
Board::Board() :
    userDirection(Direction::LEFT)
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
    level = LevelDesign::LEVEL_1;

    return true;
}

void Board::setUserDirection(Direction direction)
{
    userDirection = direction;
}

void Board::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    int colCount = 0;
    int rowCount = 4;
    for (Cell cell : level)
    {
        SDL_Rect position = {colCount * Constants::CHARACTER_SIZE, rowCount * Constants::CHARACTER_SIZE, 
            Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
        spriteSheet->selectSprite(cell.srcCol, cell.srcRow);
        spriteSheet->drawSelectedSprite(surface, &position);
        colCount++;
        if (colCount % 28 == 0 )
        {
            colCount = 0;
            rowCount++;
        }
    }

    // draw Pacman
    std::shared_ptr<Pacman> pacman = characterManager->getPacman();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_Rect pacmanPos = {pacman->getX() + (i * Constants::CHARACTER_SIZE), pacman->getY() + (j * Constants::CHARACTER_SIZE),
                Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
            spriteSheet->selectSprite(pacman->getSrcCol() + i, pacman->getSrcRow() + j);
            spriteSheet->drawSelectedSprite(surface, &pacmanPos);
        }
    }
    pacman->move();
    pacman->changeDirection(userDirection);
    
    std::vector<std::shared_ptr<Ghost>> ghosts = characterManager->getGhosts();

    for (std::shared_ptr<Ghost> ghost : ghosts)
    {
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_Rect ghostPos = {ghost->getX() + (i * Constants::CHARACTER_SIZE), ghost->getY() + (j * Constants::CHARACTER_SIZE),
                Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
            spriteSheet->selectSprite(ghost->getSrcCol() + i, ghost->getSrcRow() + j);
            spriteSheet->drawSelectedSprite(surface, &ghostPos);
        }
    }
    }

    SDL_Delay(250);
    SDL_UpdateWindowSurface(window);
}

} // namespace
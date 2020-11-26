#include "pacman/Board.hpp"
#include "pacman/Constants.hpp"

namespace pacman
{

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

void Board::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    for (Cell cell : level)
    {
        SDL_Rect position = {cell.destCol * Constants::CHARACTER_SIZE, cell.destRow * Constants::CHARACTER_SIZE, 
            Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
        spriteSheet->selectSprite(cell.srcCol, cell.srcRow);
        spriteSheet->drawSelectedSprite(surface, &position);        
    }

    // draw Pacman
    std::shared_ptr<Pacman> pacman = characterManager->getPacman();
    SDL_Rect pacmanPos1 = {pacman->getCol() * Constants::CHARACTER_SIZE, pacman->getRow() * Constants::CHARACTER_SIZE,
            Constants::CHARACTER_SIZE, Constants::CHARACTER_SIZE};
    //spriteSheet->selectSprite(pacman->getSrcRow(), pacman->getSrcCol());
    spriteSheet->selectSprite(6, 0);
    spriteSheet->drawSelectedSprite(surface, &pacmanPos1);

    
    SDL_Delay(100);
    SDL_UpdateWindowSurface(window);
}

} // namespace

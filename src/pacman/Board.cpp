#include "pacman/Board.hpp"

namespace pacman
{

Board::~Board()
{
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
}

bool Board::init()
{
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

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

    spriteSheet = std::make_unique<SpriteSheet>("resources/pacman-spritesheet.bmp", 20, 32);
    level = LevelDesign::LEVEL_1;

    return true;
}

void Board::draw()
{
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    for (Cell cell : level)
    {
        SDL_Rect position = {cell.destCol * 24, cell.destRow * 24, 24, 24};
        spriteSheet->selectSprite(cell.srcRow, cell.srcCol);
        spriteSheet->drawSelectedSprite(surface, &position);        
    }
    
    //position = {24, 0, 24, 24};
    //spriteSheet->selectSprite(26, 4);
    //spriteSheet->drawSelectedSprite(surface, &position);
    
    SDL_Delay(100);
    SDL_UpdateWindowSurface(window);
}

} // namespace

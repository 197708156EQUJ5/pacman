#include "pacman/Application.hpp"

#include "pacman/Direction.hpp"

namespace pacman
{

Application::Application()
{
    board = std::make_unique<Board>();
    board->init();
}

void Application::loop()
{
    bool hasQuit = false;
    
    while (!hasQuit)
    {
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_LEFT:
                            board->setUserDirection(Direction::LEFT);
                            break;
                        case SDLK_RIGHT:
                            board->setUserDirection(Direction::RIGHT);
                            break;
                        case SDLK_UP:
                            board->setUserDirection(Direction::UP);
                            break;
                        case SDLK_DOWN:
                            board->setUserDirection(Direction::DOWN);
                            break;
                        case SDLK_q:
                            hasQuit = true;
                            break;
                        default:
                            break;
                    }
                }
                break;
                case SDL_QUIT:
                    hasQuit = true;
                    break;
            }
        }
        board->draw();
    }
}

} // namespace

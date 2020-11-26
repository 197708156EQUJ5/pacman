#include "pacman/Application.hpp"

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
        while(SDL_PollEvent(&event) > 0)
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    hasQuit = true;
                    break;
            }
        }
        board->draw();
    }
}

} // namespace

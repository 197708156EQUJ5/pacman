#include "pacman/CharacterManager.hpp"

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

}

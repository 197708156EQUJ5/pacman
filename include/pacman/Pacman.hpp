#pragma once

#include "pacman/Character.hpp"

namespace pacman
{

class Pacman : public Character
{
public:

    Pacman(int x = PacmanConstants::START_COL * Constants::CHARACTER_SIZE, 
            int y = PacmanConstants::START_ROW * Constants::CHARACTER_SIZE, 
            Direction direction = Direction::NONE,
            bool isOddMove = false); 
    ~Pacman() = default;
    
    int getSrcCol();
    int getSrcRow();
    void move();
    void changeDirection(Direction direction);
    
private:

};

} // namespace pacman


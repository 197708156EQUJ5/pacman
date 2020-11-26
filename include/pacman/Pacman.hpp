#pragma once

#include "pacman/Character.hpp"
#include "pacman/Constants.hpp"

namespace pacman
{

class Pacman : public Character
{
public:

    Pacman(int col = PacmanConstants::START_COL, int row = PacmanConstants::START_ROW, Direction direction = Direction::LEFT);
    ~Pacman() = default;

private:

    //static const int 
};

} // namespace pacman


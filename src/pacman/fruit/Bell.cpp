#include "pacman/fruit/Bell.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Bell::Bell() :
    Fruit(FruitConstants::SRC_BELL.col, FruitConstants::SRC_BELL.row, Direction::NONE)
{
}

int Bell::getSrcCol()
{
    return FruitConstants::SRC_BELL.col;
}

int Bell::getSrcRow()
{

    return FruitConstants::SRC_BELL.row;
}

int Bell::getValue()
{
    return FruitConstants:BELL_VALUE;
}

} // namespace pacman


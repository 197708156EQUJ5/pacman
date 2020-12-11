#include "pacman/fruit/Grape.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Grape::Grape() :
    Fruit(FruitConstants::SRC_GRAPE.col, FruitConstants::SRC_GRAPE.row, Direction::NONE)
{
}

int Grape::getSrcCol()
{
    return FruitConstants::SRC_GRAPE.col;
}

int Grape::getSrcRow()
{

    return FruitConstants::SRC_GRAPE.row;
}

int Grape::getValue()
{
    return FruitConstants:GRAPE_VALUE;
}

} // namespace pacman


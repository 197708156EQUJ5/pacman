#include "pacman/fruit/Peach.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Peach::Peach() :
    Fruit(FruitConstants::SRC_PEACH.col, FruitConstants::SRC_PEACH.row, Direction::NONE)
{
}

int Peach::getSrcCol()
{
    return FruitConstants::SRC_PEACH.col;
}

int Peach::getSrcRow()
{

    return FruitConstants::SRC_PEACH.row;
}

int Peach::getValue()
{
    return FruitConstants:PEACH_VALUE;
}

} // namespace pacman


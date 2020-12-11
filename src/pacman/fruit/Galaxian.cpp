#include "pacman/fruit/Galaxian.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Galaxian::Galaxian() :
    Fruit(FruitConstants::SRC_GALAXIAN.col, FruitConstants::SRC_GALAXIAN.row, Direction::NONE)
{
}

int Galaxian::getSrcCol()
{
    return FruitConstants::SRC_GALAXIAN.col;
}

int Galaxian::getSrcRow()
{

    return FruitConstants::SRC_GALAXIAN.row;
}

int Galaxian::getValue()
{
    return FruitConstants:XXX_VALUE;
}

} // namespace pacman


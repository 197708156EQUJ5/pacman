#include "pacman/fruit/Cherry.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Cherry::Cherry() :
    Fruit(FruitConstants::SRC_CHERRY.col, FruitConstants::SRC_CHERRY.row, Direction::NONE)
{
}

int Cherry::getSrcCol()
{
    return FruitConstants::SRC_CHERRY.col;
}

int Cherry::getSrcRow()
{

    return FruitConstants::SRC_CHERRY.row;
}

int XXX::getValue()
{
    return FruitConstants::_VALUE;
}

} // namespace pacman


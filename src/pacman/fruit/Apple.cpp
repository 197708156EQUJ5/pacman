#include "pacman/fruit/Apple.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Apple::Apple() :
    Fruit(FruitConstants::SRC_APPLE.col, FruitConstants::SRC_APPLE.row, Direction::NONE)
{
}

int Apple::getSrcCol()
{
    return FruitConstants::SRC_APPLE.col;
}

int Apple::getSrcRow()
{

    return FruitConstants::SRC_APPLE.row;
}

int Apple::getValue()
{
    return FruitConstants::APPLE_VALUE;
}

} // namespace pacman


#include "pacman/fruit/Strawberry.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Strawberry::Strawberry() :
    Fruit(FruitConstants::SRC_STRAWBERRY.col, FruitConstants::SRC_STRAWBERRY.row, Direction::NONE)
{
}

int Strawberry::getSrcCol()
{
    return FruitConstants::SRC_STRAWBERRY.col;
}

int Strawberry::getSrcRow()
{

    return FruitConstants::SRC_STRAWBERRY.row;
}

int Strawberry::getValue()
{
    return FruitConstants::STRAWBERRY_VALUE;
}

} // namespace pacman


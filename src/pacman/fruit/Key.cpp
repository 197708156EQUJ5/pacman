#include "pacman/fruit/Key.hpp"

#include "pacman/Constants.hpp"

namespace pacman
{

Key::Key() :
    Fruit(FruitConstants::SRC_KEY.col, FruitConstants::SRC_KEY.row, Direction::NONE)
{
}

int Key::getSrcCol()
{
    return FruitConstants::SRC_KEY.col;
}

int Key::getSrcRow()
{

    return FruitConstants::SRC_KEY.row;
}

int Key::getValue()
{
    return FruitConstants::KEY_VALUE;
}

} // namespace pacman


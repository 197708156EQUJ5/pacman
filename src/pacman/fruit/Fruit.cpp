#include "pacman/fruit/Fruit.hpp"

#include <iostream>

namespace pacman
{

Fruit::Fruit(int x, int y, Direction direction) :
    Character(x, y, direction)
{
}

} // namespace pacman


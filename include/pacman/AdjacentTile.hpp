#pragma once

#include "pacman/Cell.hpp"
#include "pacman/Direction.hpp"

#include <vector>

namespace pacman
{

struct AdjacentTile
{
    Cell north;
    Cell west;
    Cell south;
    Cell east;

    std::vector<Cell> tiles{north, west, south, east};

    Cell fromDirection(Direction direction)
    {
        Cell cell;
        if (direction == Direction::UP)
        {
            cell = north;
        }
        else if (direction == Direction::DOWN)
        {
            cell = south;
        }
        else if (direction == Direction::LEFT)
        {
            cell = west;
        }
        else if (direction == Direction::RIGHT)
        {
            cell = east;
        }

        return cell;
    }
};

}

#pragma once

#include <sstream>

namespace pacman
{

struct Cell
{
    int col;
    int row;
    bool hasVisited = false;

    bool operator==(const Cell& rhs) const
    {
        return col == rhs.col && row == rhs.row;
    }

    bool operator!=(const Cell& rhs) const
    {
        return col != rhs.col || row != rhs.row;
    }

};

struct Tile
{
    /// upper-left corner x,y
    int x;
    int y;

    bool operator==(const Tile& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Tile& rhs) const
    {
        return x != rhs.x || y != rhs.y;
    }

};

} // namespace pacman

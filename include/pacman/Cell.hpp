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

} // namespace pacman

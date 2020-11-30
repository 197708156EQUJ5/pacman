#pragma once

namespace pacman
{

struct Cell
{
    int col;
    int row;
    bool hasVisited = false;

    bool operator==(const Cell& rhs)
    {
        return col == rhs.col && row == rhs.row;
    }

    bool operator!=(const Cell& rhs)
    {
        return col != rhs.col || row != rhs.row;
    }
};

} // namespace pacman

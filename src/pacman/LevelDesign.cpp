#include "pacman/LevelDesign.hpp"

#include "pacman/Constants.hpp"

#include <algorithm>
#include <iostream>

namespace pacman
{

const std::vector<Cell> LevelDesign::LEGAL_TILES(
{
    Cell{17, 0}, Cell{21, 0}, Cell{30, 5}
});

const Cell LevelDesign::GHOST_HOUSE_DOOR = Cell{15, 1};

std::vector<Cell> LevelDesign::LEVEL_1(
{
    // Row 1
    Cell{17, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, 
    Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{27, 5}, 
    Cell{26, 5}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4},
    Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{16, 4},
    // Row 2
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 3
    Cell{19, 4}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, 
    Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, 
    Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 4
    Cell{19, 4}, Cell{21, 0}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{17, 0}, 
    Cell{3, 8},  Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, 
    Cell{17, 0}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{21, 0}, Cell{18, 4},
    // Row 5
    Cell{19, 4}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, 
    Cell{25, 5}, Cell{0, 9},  Cell{0, 9},  Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, 
    Cell{24, 5},  Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, 
    Cell{17, 0}, Cell{25, 5}, Cell{0, 9},  Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 6
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 7
    Cell{19, 4}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, 
    Cell{23, 5}, Cell{22, 5}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, 
    Cell{30, 4},  Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{23, 5}, Cell{22, 5}, 
    Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 8
    Cell{19, 4}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8},  Cell{17, 0},  Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{19, 5}, 
    Cell{18, 5},  Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{25, 5}, Cell{0, 9},  Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 9
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{4, 8},  Cell{3, 8},  Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8},  Cell{3, 8},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 10
    Cell{21, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 3}, Cell{17, 0}, 
    Cell{4, 8},  Cell{25, 5}, Cell{0, 9},  Cell{0, 9},  Cell{22, 5}, Cell{30, 5}, Cell{4, 8}, 
    Cell{3, 8},  Cell{30, 5}, Cell{23, 5}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{3, 8},
    Cell{17, 0}, Cell{29, 3}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{20, 4},
    // Row 11
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{23, 5}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{30, 5}, Cell{25, 5}, 
    Cell{24, 5}, Cell{30, 5}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{22, 5}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 12 Blinky's start row
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 13 Ghost House Top
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{29, 3}, Cell{28, 4}, Cell{17, 5}, Cell{15, 1}, 
    Cell{15, 1}, Cell{16, 5}, Cell{28, 4}, Cell{28, 3}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 14
    Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{30, 3}, Cell{17, 0},
    Cell{25, 5}, Cell{24, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{25, 5}, Cell{24, 5},
    Cell{17, 0}, Cell{31, 3}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, 
    // Row 15 Inky, Pinky, and Clyde's start row
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{17, 0},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{17, 0}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    // Row 16
    Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 3}, Cell{17, 0},
    Cell{23, 5}, Cell{22, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{23, 5}, Cell{22, 5},
    Cell{17, 0}, Cell{29, 3}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, 
    // Row 17 Ghost House Bottom
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{31, 3}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, 
    Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{30, 3}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 18
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 19
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8},  Cell{3, 8},  Cell{30, 5}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, 
    Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 20
    Cell{17, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{30, 3}, Cell{17, 0},
    Cell{25, 5}, Cell{24, 5}, Cell{30, 5}, Cell{25, 5}, Cell{0, 9},  Cell{0, 9},  Cell{19, 5},
    Cell{18, 5}, Cell{0, 9},  Cell{0, 9},  Cell{24, 5}, Cell{30, 5}, Cell{25, 5}, Cell{24, 5},
    Cell{17, 0}, Cell{31, 3}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{16, 4},
    // Row 21
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 22
    Cell{19, 4}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, 
    Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8},  Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, 
    Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 23
    Cell{19, 4}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{22, 5}, Cell{3, 8}, Cell{17, 0}, 
    Cell{25, 5}, Cell{0, 9},  Cell{0, 9},  Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, 
    Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, 
    Cell{17, 0}, Cell{4, 8}, Cell{23, 5},  Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 24 Pacman's start row
    Cell{19, 4}, Cell{21, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, Cell{3, 8}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{30, 5}, 
    Cell{30, 5}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0},
    Cell{17, 0}, Cell{4, 8}, Cell{3, 8}, Cell{17, 0}, Cell{17, 0}, Cell{21, 0}, Cell{18, 4},
    // Row 25
    Cell{23, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{4, 8}, Cell{3, 8}, Cell{17, 0},
    Cell{23, 5}, Cell{22, 5}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4},
    Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{23, 5}, Cell{22, 5},
    Cell{17, 0}, Cell{4, 8}, Cell{3, 8}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{22, 4},
    // Row 26
    Cell{25, 4}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, Cell{24, 5}, Cell{17, 0},
    Cell{4, 8}, Cell{3, 8}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{19, 5},
    Cell{18, 5}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{4, 8}, Cell{3, 8},
    Cell{17, 0}, Cell{25, 5}, Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{24, 4},
    // Row 27
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{4, 8}, Cell{3, 8},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 28
    Cell{19, 4}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, 
    Cell{24, 5}, Cell{25, 5}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{4, 8}, 
    Cell{3, 8}, Cell{17, 0}, Cell{23, 5}, Cell{30, 4}, Cell{30, 4}, Cell{24, 5}, Cell{25, 5},
    Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{30, 4}, Cell{22, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 29
    Cell{19, 4}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, 
    Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, 
    Cell{24, 5}, Cell{17, 0}, Cell{25, 5}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, 
    Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{0, 9}, Cell{24, 5}, Cell{17, 0}, Cell{18, 4},
    // Row 30
    Cell{19, 4}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, 
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0},
    Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{17, 0}, Cell{18, 4},
    // Row 31
    Cell{21, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, 
    Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, 
    Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4},
    Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{20, 4}
});

std::vector<Cell>& LevelDesign::getLevel()
{
    std::vector<Cell>& vec = LEVEL_1;
    return vec;
}

Cell& LevelDesign::getCellType(int col, int row)
{
    return LevelDesign::LEVEL_1.at(row * Constants::COLUMN_COUNT + col);
}

bool LevelDesign::canMove(Cell cell)
{

    //if (typeid(*character) == typeid(Clyde))
    //{
    //    printf("cell_src col/row: (%2d, %2d) next_src col/row: (%2d, %2d) curr_index (%2d, %2d) next_index COL/ROW (%2d, %2d)\n", 
    //            cell.col, cell.row, nextCell.col, nextCell.row, col, row, nextCol, nextRow);
    //}
    //printf("Cell (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d) (%3d, %3d)\n", 
    //        cell.col, cell.row, nextCell.col, nextCell.row, nextCol, nextRow, col, row, centerX, centerY);
    std::vector<Cell> legalTiles = LevelDesign::LEGAL_TILES;
    if (find (legalTiles.begin(), legalTiles.end(), LevelDesign::getCellType(cell.col, cell.row)) == legalTiles.end())
    {
        return false;
    }

    return true;
}

bool LevelDesign::isLegalMove(Cell cell)
{
    std::vector<Cell> legalTiles = LevelDesign::LEGAL_TILES;
    return find (legalTiles.begin(), legalTiles.end(), LevelDesign::getCellType(cell.col, cell.row)) != legalTiles.end();
}

bool LevelDesign::isGhostHouseDoor(const Cell cell)
{
    return getCellType(cell.col, cell.row) == LevelDesign::GHOST_HOUSE_DOOR;
}

int LevelDesign::getCellValue(Cell cell)
{
    Cell& cellType = getCellType(cell.col, cell.row);

    if (cellType == Constants::PELLET && !cellType.hasVisited)
    {
        cellType.hasVisited = true;
        //printf("CellType (%2d, %2d) visted? %d\n", cellType.col, cellType.row, cellType.hasVisited);
        return 10;
    }
    else if (cellType == Constants::ENERGIZER && !cellType.hasVisited)
    {
        cellType.hasVisited = true;
        return 50;
    }

    return 0;
}

}

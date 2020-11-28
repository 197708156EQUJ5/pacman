#include "pacman/LevelDesign.hpp"

namespace pacman
{

const std::vector<Cell> LevelDesign::LEGAL_TILES(
{
    Cell{17, 0}, Cell{21, 0}, Cell{30, 5}
});

const std::vector<Cell> LevelDesign::LEVEL_1(
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
    // Row 12
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 13
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{17, 0}, 
    Cell{4, 8}, Cell{3, 8}, Cell{30, 5}, Cell{29, 3}, Cell{28, 4}, Cell{17, 5}, Cell{30, 5}, 
    Cell{30, 5}, Cell{16, 5}, Cell{28, 4}, Cell{28, 3}, Cell{30, 5}, Cell{4, 8}, Cell{3, 8}, 
    Cell{17, 0}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, 
    // Row 14
    Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{30, 3}, Cell{17, 0},
    Cell{25, 5}, Cell{24, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{25, 5}, Cell{24, 5},
    Cell{17, 0}, Cell{31, 3}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, Cell{26, 4}, 
    // Row 15
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{17, 0},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{17, 0}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    // Row 16
    Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 3}, Cell{17, 0},
    Cell{23, 5}, Cell{22, 5}, Cell{30, 5}, Cell{18, 4}, Cell{30, 5}, Cell{30, 5}, Cell{30, 5},
    Cell{30, 5}, Cell{30, 5}, Cell{30, 5}, Cell{19, 4}, Cell{30, 5}, Cell{23, 5}, Cell{22, 5},
    Cell{17, 0}, Cell{29, 3}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, Cell{28, 4}, 
    // Row 17
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
    // Row 24
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
}

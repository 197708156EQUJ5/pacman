#pragma once

#include "Cell.hpp"

namespace Constants
{

//Screen dimension constants
static const int TILE_DISPLAY_RATIO = 3;
static const int BOARD_WIDTH = 224 * TILE_DISPLAY_RATIO;
static const int BOARD_HEIGHT = 288 * TILE_DISPLAY_RATIO;
static const int SS_COLS = 32;
static const int SS_ROWS = 20;
static const int TILE_SIZE = 8;
static const int TITLE_ROW_COUNT = 3;
static const int TOP_ROW_OFFSET = TITLE_ROW_COUNT * TILE_SIZE;

static const int COLUMN_COUNT = 28;
static const char *SPRITESHEET_PATH = "resources/pacman-spritesheet.bmp";
static const int MAZE_ROW_OFFSET = 4;
static const int MAXIMUM_PIXEL_SPEED = 1;

static const int NUM_ROW = 0;
static const int NUM_COL_0 = 0;
static const int NUM_COL_1 = 1;
static const int NUM_COL_2 = 2;
static const int NUM_COL_3 = 3;
static const int NUM_COL_4 = 4;
static const int NUM_COL_5 = 5;
static const int NUM_COL_6 = 6;
static const int NUM_COL_7 = 7;
static const int NUM_COL_8 = 8;
static const int NUM_COL_9 = 9;
static const pacman::Cell A{1, 2};
static const pacman::Cell B{2, 2};
static const pacman::Cell C{3, 2};
static const pacman::Cell D{4, 2};
static const pacman::Cell E{5, 2};
static const pacman::Cell F{6, 2};
static const pacman::Cell G{7, 2};
static const pacman::Cell H{8, 2};
static const pacman::Cell I{9, 2};
static const pacman::Cell J{10, 2};
static const pacman::Cell K{11, 2};
static const pacman::Cell L{12, 2};
static const pacman::Cell M{13, 2};
static const pacman::Cell N{14, 2};
static const pacman::Cell O{15, 2};
static const pacman::Cell P{16, 2};
static const pacman::Cell Q{17, 2};
static const pacman::Cell R{18, 2};
static const pacman::Cell S{19, 2};
static const pacman::Cell T{20, 2};
static const pacman::Cell U{21, 2};
static const pacman::Cell V{22, 2};
static const pacman::Cell W{23, 2};
static const pacman::Cell X{24, 2};
static const pacman::Cell Y{25, 2};
static const pacman::Cell Z{26, 2};
static const pacman::Cell PELLET{17, 0};
static const pacman::Cell ENERGIZER{21, 0};
static const pacman::Cell EMPTY{30, 5};

}

namespace PacmanConstants
{

static const int START_COL = 112; // 14th column
static const int START_ROW = 212; // 26th row including score header, centered

static const int SRC_ROW = 6;
static const int SRC_START_COL = 0;
static const int SRC_START_ROW = 14;
static const int SRC_LEFT_1 = 0;
static const int SRC_LEFT_2 = 4;
static const int SRC_RIGHT_1 = 8;
static const int SRC_RIGHT_2 = 12;
static const int SRC_UP_1 = 2;
static const int SRC_UP_2 = 6;
static const int SRC_DOWN_1 = 10;
static const int SRC_DOWN_2 = 14;

}

namespace GhostConstants
{


}

namespace BlinkyConstants
{

static const int START_COL = 112; // 14th column
static const int START_ROW = 116; // 14th row plus half row offset

static const int SRC_ROW = 12;
static const int SRC_LEFT_1 = 8;
static const int SRC_LEFT_2 = 10;
static const int SRC_RIGHT_1 = 0;
static const int SRC_RIGHT_2 = 2;
static const int SRC_UP_1 = 12;
static const int SRC_UP_2 = 14;
static const int SRC_DOWN_1 = 4;
static const int SRC_DOWN_2 = 6;

static const int SCATTER_COL = 204; // 25th column, centered
static const int SCATTER_ROW = 4; // 0th row, centered

}

namespace PinkyConstants
{

static const int START_COL = 112; // 14th column
static const int START_ROW = 140; // 17th row plus half row offset

static const int SRC_ROW = 16;
static const int SRC_LEFT_1 = 8;
static const int SRC_LEFT_2 = 10;
static const int SRC_RIGHT_1 = 0;
static const int SRC_RIGHT_2 = 2;
static const int SRC_UP_1 = 12;
static const int SRC_UP_2 = 14;
static const int SRC_DOWN_1 = 4;
static const int SRC_DOWN_2 = 6;

//static const int SCATTER_COL = 20; // 2nd column (0 index), centered
//static const int SCATTER_ROW = 4; // 0th row, centered
static const int SCATTER_COL = 4; // 0th column (0 index), centered
static const int SCATTER_ROW = 284; // 35th row, centered

}

namespace InkyConstants
{

static const int START_COL = 96; // 8th column
static const int START_ROW = 140; // 17th row plus half row offset

static const int SRC_ROW = 16;
static const int SRC_LEFT_1 = 24;
static const int SRC_LEFT_2 = 26;
static const int SRC_RIGHT_1 = 16;
static const int SRC_RIGHT_2 = 18;
static const int SRC_UP_1 = 28;
static const int SRC_UP_2 = 30;
static const int SRC_DOWN_1 = 20;
static const int SRC_DOWN_2 = 22;

static const int SCATTER_COL = 4; // 0th column (0 index), centered
static const int SCATTER_ROW = 284; // 35th row, centered

}

namespace ClydeConstants
{

static const int START_COL = 128; // 15th column
static const int START_ROW = 140; // 17th row plus half row offset

static const int SRC_ROW = 18;
static const int SRC_LEFT_1 = 8;
static const int SRC_LEFT_2 = 10;
static const int SRC_RIGHT_1 = 0;
static const int SRC_RIGHT_2 = 2;
static const int SRC_UP_1 = 12;
static const int SRC_UP_2 = 14;
static const int SRC_DOWN_1 = 4;
static const int SRC_DOWN_2 = 6;

static const int SCATTER_COL = 220; // 0th column (0 index), centered
static const int SCATTER_ROW = 284; // 35th row, centered

}

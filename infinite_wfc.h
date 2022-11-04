#pragma once

#include "wfc.h"
#include "avl_tree.h"

#define C_UP 0
#define C_LEFT 1
#define C_DOWN 2
#define C_RIGHT 3

extern AVLTree* allBlocks;

void genConstraint(BlockMap* from, BlockMap* to, uint direction);
void genBlock(int x, int y, bool isFirst);
void genMap(int x, int y, BlockMap* blockMap, bool isFirst);
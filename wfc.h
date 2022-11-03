#pragma once

typedef unsigned int uint;

struct Module
{
	uint id;
	bool upId;
	bool leftId;
	bool downId;
	bool rightId;
	float probability;
};

struct Block
{
	uint id;
	uint availableModules;
	bool entropyOutdated;
	double entropy;
};

struct BlockMap
{
	Block** blocks;
};

extern Module modules[16];

void initModules();
BlockMap initBlockMap();
void calculateEntropy(Block* block);
void collapse(Block** blocks, int x, int y);
void collapseAll(Block** blocks);
#include "wfc.h"
#include <cstdlib>
#include <math.h>
#include <limits>
Module modules[16];

void initModules()
{
    modules[0x0] = { 1 << 0x0, 0, 0, 0, 0, 0.1796875 };
    modules[0x1] = { 1 << 0x1, 1, 0, 1, 0, 0.0546875 };
    modules[0x2] = { 1 << 0x2, 0, 1, 0, 1, 0.0546875 };
    modules[0x3] = { 1 << 0x3, 1, 1, 0, 0, 0.0546875 };
    modules[0x4] = { 1 << 0x4, 0, 1, 1, 0, 0.0546875 };
    modules[0x5] = { 1 << 0x5, 0, 0, 1, 1, 0.0546875 };
    modules[0x6] = { 1 << 0x6, 1, 0, 0, 1, 0.0546875 };
    modules[0x7] = { 1 << 0x7, 1, 1, 1, 0, 0.0546875 };
    modules[0x8] = { 1 << 0x8, 1, 1, 0, 1, 0.0546875 };
    modules[0x9] = { 1 << 0x9, 1, 0, 1, 1, 0.0546875 };
    modules[0xa] = { 1 << 0xa, 0, 1, 1, 1, 0.0546875 };
    modules[0xb] = { 1 << 0xb, 1, 1, 1, 1, 0.0546875 };
    modules[0xc] = { 1 << 0xc, 0, 0, 0, 1, 0.0546875 };
    modules[0xd] = { 1 << 0xd, 0, 0, 1, 0, 0.0546875 };
    modules[0xe] = { 1 << 0xe, 0, 1, 0, 0, 0.0546875 };
    modules[0xf] = { 1 << 0xf, 1, 0, 0, 0, 0.0546875 };
}

BlockMap initBlockMap()
{
    BlockMap out;
    void* temp = malloc(64 * sizeof(Block));
    out.blocks = (Block**)malloc(8 * sizeof(Block*));
    for (int i = 0; i < 8; i++)
    {
        out.blocks[i] = (Block*)temp + i * 8;
        for (int j = 0; j < 8; j++)
        {
            out.blocks[i][j].id = -1;
            out.blocks[i][j].availableModules = 0xffff;
            out.blocks[i][j].entropyOutdated = true;
        }
    }
    return out;
}

void calculateEntropy(Block* block)
{
    if (!block->entropyOutdated)
        return;

    block->entropyOutdated = false;

    double total = 0;
    double entropySum = 0;

    for (int i = 0; i < 16; i++)
    {
        if (modules[i].id & block->availableModules)
        {
            total += modules[i].probability;
            entropySum += modules[i].probability * log(modules[i].probability);
        }
    }

    block->entropy = -1.0 / total * entropySum + log(total);
}

void collapse(Block** blocks, int x, int y)
{
    Block* block = blocks[x] + y;
    double max = 0;
    for (int i = 0; i < 16; i++)
        if (block->availableModules & modules[i].id)
            max += modules[i].probability;

    double roll = (rand() / 32767.0) * max;
    for (int i = 0; i < 16; i++)
    {
        if (block->availableModules & modules[i].id)
        {
            roll -= modules[i].probability;
            if (roll <= 0)
            {
                block->id = i;
                break;
            }
        }
    }

    if (block->id == -1)
        block->id = 0;

    if (y > 0)
    {
        if (modules[block->id].upId)
        {
            uint temp = blocks[x][y - 1].availableModules;
            blocks[x][y - 1].availableModules &= 0b0010111010110010;
            if (temp != blocks[x][y - 1].availableModules)
                blocks[x][y - 1].entropyOutdated = true;
        }
        else
        {
            uint temp = blocks[x][y - 1].availableModules;
            blocks[x][y - 1].availableModules &= 0b1101000101001101;
            if (temp != blocks[x][y - 1].availableModules)
                blocks[x][y - 1].entropyOutdated = true;
        }
    }
    if (x > 0)
    {
        if (modules[block->id].leftId)
        {
            uint temp = blocks[x - 1][y].availableModules;
            blocks[x - 1][y].availableModules &= 0b0001111101100100;
            if (temp != blocks[x - 1][y].availableModules)
                blocks[x - 1][y].entropyOutdated = true;
        }
        else
        {
            uint temp = blocks[x - 1][y].availableModules;
            blocks[x - 1][y].availableModules &= 0b1110000010011011;
            if (temp != blocks[x - 1][y].availableModules)
                blocks[x - 1][y].entropyOutdated = true;
        }
    }
    if (y < 7)
    {
        if (modules[block->id].downId)
        {
            uint temp = blocks[x][y + 1].availableModules;
            blocks[x][y + 1].availableModules &= 0b1000101111001010;
            if (temp != blocks[x][y + 1].availableModules)
                blocks[x][y + 1].entropyOutdated = true;
        }
        else
        {
            uint temp = blocks[x][y + 1].availableModules;
            blocks[x][y + 1].availableModules &= 0b0111010000110101;
            if (temp != blocks[x][y + 1].availableModules)
                blocks[x][y + 1].entropyOutdated = true;
        }
    }
    if (x < 7)
    {
        if (modules[block->id].rightId)
        {
            uint temp = blocks[x + 1][y].availableModules;
            blocks[x + 1][y].availableModules &= 0b0100110110011100;
            if (temp != blocks[x + 1][y].availableModules)
                blocks[x + 1][y].entropyOutdated = true;
        }
        else
        {
            uint temp = blocks[x + 1][y].availableModules;
            blocks[x + 1][y].availableModules &= 0b1011001001100011;
            if (temp != blocks[x + 1][y].availableModules)
                blocks[x + 1][y].entropyOutdated = true;
        }
    }
}

void collapseAll(Block** blocks)
{
    double minEntropy = std::numeric_limits<double>::infinity();
    int currentId = 0;

    for (int i = 0; i < 64; i++)
    {
        minEntropy = std::numeric_limits<double>::infinity();
        for (int j = 0; j < 64; j++)
        {
            calculateEntropy(blocks[0] + j);

            if (blocks[0][j].entropy < minEntropy && blocks[0][j].id > 16)
            {
                minEntropy = blocks[0][j].entropy;
                currentId = j;
            }
        }

        collapse(blocks, currentId >> 3, currentId & 0b111);
    }
}
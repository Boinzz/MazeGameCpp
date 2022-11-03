#include "infinite_wfc.h"
#include "game_logic_top.h"

AVLTree* allBlocks;

void genConstraint(BlockMap* from, BlockMap* to, uint direction)
{
	switch (direction)
	{
	case C_UP:
		for (int i = 0; i < 8; i++)
		{
			if (modules[from->blocks[i][0].id].upId)
				to->blocks[i][7].availableModules &= 0b0010111010110010;
			else
				to->blocks[i][7].availableModules &= 0b1101000101001101;
		}
		break;
	case C_LEFT:
		for (int i = 0; i < 8; i++)
		{
			if (modules[from->blocks[0][i].id].leftId)
				to->blocks[7][i].availableModules &= 0b0001111101100100;
			else
				to->blocks[7][i].availableModules &= 0b1110000010011011;
		}
		break;
	case C_DOWN:
		for (int i = 0; i < 8; i++)
		{
			if (modules[from->blocks[i][7].id].downId)
				to->blocks[i][0].availableModules &= 0b1000101111001010;
			else
				to->blocks[i][0].availableModules &= 0b0111010000110101;
		}
		break;
	case C_RIGHT:
		for (int i = 0; i < 8; i++)
		{
			if (modules[from->blocks[7][i].id].rightId)
				to->blocks[0][i].availableModules &= 0b0100110110011100;
			else
				to->blocks[0][i].availableModules &= 0b1011001001100011;
		}
		break;
	}
}

void genBlock(int x, int y)
{
	AVLTreeNode* result = search(allBlocks, (x & 0xffff) + (y << 16));
	if (result != nullptr)
		return;

	BlockMap* out = new BlockMap[1];
	*out = initBlockMap();

	result = search(allBlocks, ((x - 1) & 0xffff) + (y << 16));
	if (result)
		genConstraint((BlockMap*)result->value, out, C_RIGHT);
	result = search(allBlocks, (x & 0xffff) + ((y - 1) << 16));
	if (result)
		genConstraint((BlockMap*)result->value, out, C_UP);
	result = search(allBlocks, ((x + 1) & 0xffff) + (y << 16));
	if (result)
		genConstraint((BlockMap*)result->value, out, C_LEFT);
	result = search(allBlocks, (x & 0xffff) + ((y + 1) << 16));
	if (result)
		genConstraint((BlockMap*)result->value, out, C_DOWN);

	collapseAll(out->blocks);

	insert(allBlocks, (x & 0xffff) + (y << 16), (void*)out);
	genMap(x, y, out);
}

void genMap(int x, int y, BlockMap* blockMap)
{
	int actualX;
	int actualY;
	GameObject* tile;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			actualX = (x * 8 + i) * 192;
			actualY = (y * 8 + j) * 192;
			switch (blockMap->blocks[i][j].id)
			{
			case 0x0:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x1:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x2:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x3:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x4:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x5:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x6:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x7:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x8:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0x9:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xa:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xb:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xc:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xd:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xe:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			case 0xf:
				tile = createTile(actualX, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 64, true);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 64, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 1) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 64, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 1) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				tile = createTile(actualX + 128, actualY + 128, false);
				insert(GAME_INSTANCE.underground.tilesMap, ((actualX / 64 + 2) & 0xffff) + ((actualY / 64 + 2) << 16), (void*)tile);
				addToMap(&GAME_INSTANCE.underground, tile, TILE);

				break;
			}
		}
	}
}

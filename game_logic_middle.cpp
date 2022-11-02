#include "game_logic_middle.h"
#include "game_logic_base.h"
#include "game_logic_top.h"
#include "resource.h"

ObjDefList objDefList;

void loadGame()
{
	//TODO: 添加实际上的游戏初始化操作
	objDefList.player = initPlayer();
	objDefList.enemy = initEnemy();
	objDefList.wall = initWall();
	objDefList.ground = initGround();

	GAME_INSTANCE.player = (Player*)createPlayer();
	GAME_INSTANCE.playerOnGround = true;
	initMap();
	addToMap(&GAME_INSTANCE.ground, (GameObject*)GAME_INSTANCE.player, DESTROYABLE);
	addToMap(&GAME_INSTANCE.ground, createEnemy(100, 100, 100, 0), DESTROYABLE);

	createGround();
}

void renderGameObjects(PaintDevice canvas)
{
	List currentTile;
	List currentDestroyable;
	List currentBullet;
	if (GAME_INSTANCE.playerOnGround)
	{
		currentTile = GAME_INSTANCE.ground.tilesHead;
		currentDestroyable = GAME_INSTANCE.ground.destroyablesHead;
		currentBullet = GAME_INSTANCE.ground.bulletsHead;
	}
	else
	{
		currentTile = GAME_INSTANCE.underground.tilesHead;
		currentDestroyable = GAME_INSTANCE.underground.destroyablesHead;
		currentBullet = GAME_INSTANCE.underground.bulletsHead;
	}

	while (currentTile != nullptr)
	{
		renderGameObject(currentTile->value, canvas);
		currentTile = currentTile->next;
	}
	while (currentDestroyable != nullptr)
	{
		renderGameObject(currentDestroyable->value, canvas);
		currentDestroyable = currentDestroyable->next;
	}
	while (currentBullet != nullptr)
	{
		renderGameObject(currentBullet->value, canvas);
		currentBullet = currentBullet->next;
	}
}

void renderGameObject(GameObject* obj, PaintDevice canvas)
{
	int actualX = obj->posX - GAME_INSTANCE.player->posX + 640 - 32;
	int actualY = obj->posY - GAME_INSTANCE.player->posY + 384 - 32;
	if (actualX < -64 || actualY < -64 || actualX > 1344 || actualY > 832)
		return;
	PaintDevice bmpCanvas = CreateCompatibleDC(canvas);
	Bitmap frame = obj->def->frames[obj->currentFrame];
	SelectObject(bmpCanvas, frame);
	//TODO: 计算下一帧应该为哪张图片
	BitBlt(canvas, actualX, actualY, 64, 64, bmpCanvas, 0, 0, SRCCOPY);
	DeleteDC(bmpCanvas);
}

void gameLogic()
{
	List currentTile;
	List currentDestroyable;
	List currentBullet;
	if (GAME_INSTANCE.playerOnGround)
	{
		currentTile = GAME_INSTANCE.ground.tilesHead;
		currentDestroyable = GAME_INSTANCE.ground.destroyablesHead;
		currentBullet = GAME_INSTANCE.ground.bulletsHead;
	}
	else
	{
		currentTile = GAME_INSTANCE.underground.tilesHead;
		currentDestroyable = GAME_INSTANCE.underground.destroyablesHead;
		currentBullet = GAME_INSTANCE.underground.bulletsHead;
	}

	while (currentTile != nullptr)
	{
		currentTile->value->tick++;
		currentTile = currentTile->next;
	}
	while (currentDestroyable != nullptr)
	{
		currentDestroyable->value->tick++;

		if (currentDestroyable->value->def->id == objDefList.enemy.id)
		{
			enemyLogic((Enemy*)currentDestroyable->value);
		}

		currentDestroyable = currentDestroyable->next;
	}
	while (currentBullet != nullptr)
	{
		currentBullet->value->tick++;
		currentBullet = currentBullet->next;
	}

	playerLogic();
}

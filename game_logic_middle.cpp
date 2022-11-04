#include "game_logic_middle.h"
#include "game_logic_base.h"
#include "game_logic_top.h"
#include "wfc.h"

ObjDefList objDefList;

void loadGame()
{
	//TODO: 添加实际上的游戏初始化操作
	initModules();
	objDefList.player = initPlayer();
	objDefList.enemy = initEnemy();
	objDefList.wall = initWall();
	objDefList.ground = initGround();
	objDefList.tower = initTower();

	GAME_INSTANCE.player = (Player*)createPlayer();
	GAME_INSTANCE.player->mapId = 1;
	GAME_INSTANCE.playerOnGround = false;

	initMap();
	addToMap(&GAME_INSTANCE.underground, (GameObject*)GAME_INSTANCE.player, DESTROYABLE);

	GAME_INSTANCE.towers = new Tower * [4];
	GameObject* temp;
	temp = createTower(128, 128);
	GAME_INSTANCE.towers[0] = (Tower*)temp;
	addToMap(&GAME_INSTANCE.ground, temp, DESTROYABLE);
	temp = createTower(128, -128);
	GAME_INSTANCE.towers[1] = (Tower*)temp;
	addToMap(&GAME_INSTANCE.ground, temp, DESTROYABLE);
	temp = createTower(-128, 128);
	GAME_INSTANCE.towers[2] = (Tower*)temp;
	addToMap(&GAME_INSTANCE.ground, temp, DESTROYABLE);
	temp = createTower(-128, -128);
	GAME_INSTANCE.towers[3] = (Tower*)temp;
	addToMap(&GAME_INSTANCE.ground, temp, DESTROYABLE);

	addToMap(&GAME_INSTANCE.ground, createEnemy(-800, -200, 100, 0), DESTROYABLE);

	createGround();
	createUnderground();
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

	AlphaBlend(canvas, actualX, actualY, 64, 64, bmpCanvas, 0, 0, 64, 64, {AC_SRC_OVER, 0, 0xff, AC_SRC_ALPHA});
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

	while (currentDestroyable->value->toBeDestroyed)
	{
		void* temp = (void*)currentDestroyable;
		void* temp2 = (void*)currentDestroyable->value;
		currentDestroyable = currentDestroyable->next;
		free(temp);
		free(temp2);
	}
	if (GAME_INSTANCE.playerOnGround)
		GAME_INSTANCE.ground.destroyablesHead = currentDestroyable;
	else
		GAME_INSTANCE.underground.destroyablesHead = currentDestroyable;

	List temp = currentDestroyable;
	while (temp != nullptr)
	{
		while (temp->next != nullptr && temp->next->value->toBeDestroyed)
		{
			void* temp2 = (void*)temp->next;
			void* temp3 = (void*)temp->next->value;
			temp->next = temp->next->next;
			free(temp2);
			free(temp3);
		}
		temp = temp->next;
	}

	if (GAME_INSTANCE.player->hp <= 0)
		PostQuitMessage(0);
	if (GAME_INSTANCE.towers[0]->hp <= 0 && GAME_INSTANCE.towers[1]->hp <= 0 && GAME_INSTANCE.towers[2]->hp <= 0 && GAME_INSTANCE.towers[3]->hp <= 0)
		PostQuitMessage(0);

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

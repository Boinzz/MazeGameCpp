#include "game_logic_middle.h"
#include "game_logic_base.h"
#include "resource.h"

void loadGame()
{
	//TODO: 添加实际上的游戏初始化操作
	Bitmap tempBmp = loadBitmap(L"testPlayer.bmp", 64, 64);
	GameObjectDef* playerDef = (GameObjectDef*)malloc(sizeof GameObjectDef);
	playerDef->frameCount = 1;
	playerDef->frames = (Bitmap*)malloc(sizeof Bitmap);
	playerDef->frames[0] = tempBmp;
	GAME_INSTANCE.player = (Player*)malloc(sizeof Player);
	GAME_INSTANCE.player->def = playerDef;
	GAME_INSTANCE.player->currentFrame = 0;
	GAME_INSTANCE.ground.tiles = nullptr;
	GAME_INSTANCE.ground.destroyables = (ListNode*)malloc(sizeof ListNode);
	GAME_INSTANCE.ground.destroyables->value = (GameObject*)GAME_INSTANCE.player;
	GAME_INSTANCE.ground.destroyables->next = nullptr;
	GAME_INSTANCE.ground.bullets = nullptr;
	GAME_INSTANCE.playerOnGround = true;
}

void renderGameObjects(PaintDevice canvas)
{
	List currentTile;
	List currentDestroyable;
	List currentBullet;
	if (GAME_INSTANCE.playerOnGround)
	{
		currentTile = GAME_INSTANCE.ground.tiles;
		currentDestroyable = GAME_INSTANCE.ground.destroyables;
		currentBullet = GAME_INSTANCE.ground.bullets;
	}
	else
	{
		currentTile = GAME_INSTANCE.underground.tiles;
		currentDestroyable = GAME_INSTANCE.underground.destroyables;
		currentBullet = GAME_INSTANCE.underground.bullets;
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
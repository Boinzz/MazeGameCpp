#include "game_logic_top.h"
#include "game_logic_base.h"
#include "game_logic_middle.h"
#include "avl_tree.h"
#include "infinite_wfc.h"
#include <math.h>


static int currentDefId = 0;
static int currentObjId = 0;


GameObjectDef initPlayer()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;
	out.frameCount = 12;
	out.frameLengths = new int[12];
	for (int i = 0; i < 12; i++)
	{
		out.frameLengths[i] = 5;
	}
	out.frames = new Bitmap[12];

	out.frames[0x0] = loadBitmap(L"./player/player0.bmp", 64, 64);
	out.frames[0x1] = loadBitmap(L"./player/player1.bmp", 64, 64);
	out.frames[0x2] = loadBitmap(L"./player/player2.bmp", 64, 64);
	out.frames[0x3] = loadBitmap(L"./player/player3.bmp", 64, 64);
	out.frames[0x4] = loadBitmap(L"./player/player4.bmp", 64, 64);
	out.frames[0x5] = loadBitmap(L"./player/player5.bmp", 64, 64);
	out.frames[0x6] = loadBitmap(L"./player/player6.bmp", 64, 64);
	out.frames[0x7] = loadBitmap(L"./player/player7.bmp", 64, 64);
	out.frames[0x8] = loadBitmap(L"./player/player8.bmp", 64, 64);
	out.frames[0x9] = loadBitmap(L"./player/player9.bmp", 64, 64);
	out.frames[0xa] = loadBitmap(L"./player/playerA.bmp", 64, 64);
	out.frames[0xb] = loadBitmap(L"./player/playerB.bmp", 64, 64);

	return out;
}

GameObjectDef initEnemy()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;
	out.frameCount = 8;
	out.frameLengths = new int[8];
	for (int i = 0; i < 8; i++)
	{
		out.frameLengths[i] = 10;
	}
	out.frames = new Bitmap[8];

	out.frames[0] = loadBitmap(L"./enemy/enemy0.bmp", 64, 64);
	out.frames[1] = loadBitmap(L"./enemy/enemy1.bmp", 64, 64);
	out.frames[2] = loadBitmap(L"./enemy/enemy2.bmp", 64, 64);
	out.frames[3] = loadBitmap(L"./enemy/enemy3.bmp", 64, 64);
	out.frames[4] = loadBitmap(L"./enemy/enemy4.bmp", 64, 64);
	out.frames[5] = loadBitmap(L"./enemy/enemy5.bmp", 64, 64);
	out.frames[6] = loadBitmap(L"./enemy/enemy6.bmp", 64, 64);
	out.frames[7] = loadBitmap(L"./enemy/enemy7.bmp", 64, 64);

	return out;
}

GameObjectDef initWall()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;

	out.frameCount = 1;
	out.frameLengths = new int[1];
	out.frameLengths[0] = 0x7fffffff;
	out.frames = new Bitmap[1];
	out.frames[0] = loadBitmap(L"./map/wall.bmp", 64, 64);

	return out;
}

GameObjectDef initGround()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;

	out.frameCount = 1;
	out.frameLengths = new int[1];
	out.frameLengths[0] = 0x7fffffff;
	out.frames = new Bitmap[1];
	out.frames[0] = loadBitmap(L"./map/ground.bmp", 64, 64);

	return out;
}

GameObjectDef initTower()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;
	out.frameCount = 2;
	out.frameLengths = new int[2];
	out.frameLengths[0] = 0x7fffffff;
	out.frameLengths[1] = 0x7fffffff;
	out.frames = new Bitmap[2];
	out.frames[0] = loadBitmap(L"./tower/tower0.bmp", 64, 64);
	out.frames[1] = loadBitmap(L"./tower/tower1.bmp", 64, 64);

	return out;
}

GameObjectDef initBullet()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 16;
	out.width = 16;
	out.frameCount = 1;
	out.frameLengths = new int[1];
	out.frameLengths[0] = 0x7fffffff;
	out.frames = new Bitmap[1];
	out.frames[0] = loadBitmap(L"./map/bullet.bmp", 16, 16);
	return out;
}

GameObjectDef initGate()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;

	out.frameCount = 1;
	out.frameLengths = new int[1];
	out.frameLengths[0] = 0x7fffffff;
	out.frames = new Bitmap[1];
	out.frames[0] = loadBitmap(L"./map/gate.bmp", 64, 64);

	return out;
}

GameObjectDef initCoin()
{
	GameObjectDef out;
	out.id = currentDefId;
	currentDefId++;
	out.height = 64;
	out.width = 64;

	out.frameCount = 1;
	out.frameLengths = new int[1];
	out.frameLengths[0] = 0x7fffffff;
	out.frames = new Bitmap[1];
	out.frames[0] = loadBitmap(L"./map/coin.bmp", 64, 64);
	return out;
}

GameObject* createPlayer()
{
	Player* out = (Player*)malloc(sizeof Player);
	out->id = currentObjId;
	currentObjId++;
	out->def = &objDefList.player;
	out->attacking = false;
	out->coins = 0;
	out->currentFrame = 7;
	out->nextFrame = 7;
	out->hp = 500;
	out->level = 0;
	out->mapId = 0;
	out->moveStatus = MV_STILL;
	out->posX = 0;
	out->posY = 65;
	out->speed = 8;
	out->tick = 0;
	out->toBeDestroyed = false;

	return (GameObject*)out;
}

GameObject* createEnemy(int posX, int posY, int hp, int mapId)
{
	Enemy* out = (Enemy*)malloc(sizeof Enemy);
	out->def = &objDefList.enemy;
	out->id = currentObjId;
	currentObjId++;
	out->mapId = mapId;
	out->posX = posX;
	out->posY = posY;
	out->hp = hp;
	out->moveStatus = MV_STILL;
	out->currentFrame = 5;
	out->nextFrame = 4;
	out->speed = 4;
	out->tick = 0;
	out->toBeDestroyed = false;
	out->targetId = GAME_INSTANCE.towers[rand() % 4]->id;

	return (GameObject*)out;
}

GameObject* createTile(int posX, int posY, bool isWall)
{
	MapTile* out = (MapTile*)malloc(sizeof MapTile);
	if (isWall)
	{
		out->def = &objDefList.wall;
		out->walkable = false;
	}
	else
	{
		out->def = &objDefList.ground;
		out->walkable = true;
	}
	out->id = currentObjId;
	currentObjId++;
	out->currentFrame = 0;
	out->nextFrame = 0;
	out->posX = posX;
	out->posY = posY;
	out->tick = 0;
	out->toBeDestroyed = false;
	
	return (GameObject*)out;
}

GameObject* createTower(int posX, int posY)
{
	Tower* out = (Tower*)malloc(sizeof Tower);

	out->id = currentObjId;
	currentObjId++;
	out->def = &objDefList.tower;
	out->currentFrame = 0;
	out->nextFrame = 0;
	out->posX = posX;
	out->posY = posY;
	out->tick = 0;
	out->hp = 1000;
	out->level = 0;
	out->toBeDestroyed = false;

	return (GameObject*)out;
}

GameObject* createBullet(int posX, int posY, double velX, double velY, int damage)
{
	Bullet* out = (Bullet*)malloc(sizeof Bullet);
	out->id = currentObjId;
	currentObjId++;
	out->def = &objDefList.bullet;
	out->currentFrame = 0;
	out->nextFrame = 0;
	out->posX = posX;
	out->posY = posY;
	out->tick = 0;
	out->velX = velX;
	out->velY = velY;
	out->toBeDestroyed = false;
	out->damage = damage;
	return (GameObject*)out;
}

GameObject* createGate()
{
	MapTile* out = (MapTile*)malloc(sizeof MapTile);

	out->id = currentObjId;
	currentObjId++;
	out->walkable = true;
	out->def = &objDefList.gate;
	out->currentFrame = 0;
	out->nextFrame = 0;
	out->tick = 0;
	out->toBeDestroyed = false;
	out->posX = 0;
	out->posY = 0;

	return (GameObject*)out;
}

GameObject* createCoin(int posX, int posY)
{
	Destroyable* out = (Destroyable*)malloc(sizeof Destroyable);
	out->id = currentObjId;
	currentObjId++;
	out->def = &objDefList.coin;
	out->posX = posX;
	out->posY = posY;
	out->mapId = 1;
	out->currentFrame = 0;
	out->nextFrame = 0;
	out->tick = 0;
	out->hp = 1;
	out->toBeDestroyed = false;
	return (GameObject*)out;
}

void initMap()
{
	GAME_INSTANCE.ground.bulletsHead = nullptr;
	GAME_INSTANCE.ground.bulletsEnd = nullptr;
	GAME_INSTANCE.ground.destroyablesHead = nullptr;
	GAME_INSTANCE.ground.destroyablesEnd = nullptr;
	GAME_INSTANCE.ground.tilesHead = nullptr;
	GAME_INSTANCE.ground.tilesEnd = nullptr;
	GAME_INSTANCE.ground.tilesMap = createTree();

	GAME_INSTANCE.underground.bulletsHead = nullptr;
	GAME_INSTANCE.underground.bulletsEnd = nullptr;
	GAME_INSTANCE.underground.destroyablesHead = nullptr;
	GAME_INSTANCE.underground.destroyablesEnd = nullptr;
	GAME_INSTANCE.underground.tilesHead = nullptr;
	GAME_INSTANCE.underground.tilesEnd = nullptr;
	GAME_INSTANCE.underground.tilesMap = createTree();
}

void createGround()
{
	GameObject* tile;
	for (int i = -14 * 64; i < 15 * 64; i += 64)
	{
		for (int j = -14 * 64; j < 15 * 64; j += 64)
		{
			if (i == 0 && j == 0)
				tile = createGate();
			else
				tile = createTile(i, j, false);
			addToMap(&GAME_INSTANCE.ground, tile, TILE);
			unsigned int index = ((i / 64) & 0xffff) + ((j / 64) << 16);
			insert(GAME_INSTANCE.ground.tilesMap, index, (void*)tile);
		}
	}
}

void createUnderground()
{
	allBlocks = createTree();
	genBlock(0, 0, true);
}

void infiniteGenMap(int x, int y)
{
	int x1 = x >> 6;
	int y1 = y >> 6;
	int x2 = x1 / 24;
	int y2 = y1 / 24;
	if (x1 < 0 && x1 % 24 != 0)
		x2--;
	if (y1 < 0 && y1 % 24 != 0)
		y2--;

	genBlock(x2, y2, false);
	genBlock(x2 - 1, y2, false);
	genBlock(x2, y2 - 1, false);
	genBlock(x2 + 1, y2, false);
	genBlock(x2, y2 + 1, false);
	genBlock(x2 - 1, y2 - 1, false);
	genBlock(x2 - 1, y2 + 1, false);
	genBlock(x2 + 1, y2 - 1, false);
	genBlock(x2 + 1, y2 + 1, false);
}

void addToMap(Map* map, GameObject* obj, ObjType type)
{
	ListNode* node = (ListNode*)malloc(sizeof ListNode);
	node->value = obj;
	node->next = nullptr;
	switch (type)
	{
	case BULLET:
		if (map->bulletsHead == nullptr)
		{
			map->bulletsHead = node;
			map->bulletsEnd = node;
		}
		else
		{
			map->bulletsEnd->next = node;
			map->bulletsEnd = node;
		}
		break;
	case DESTROYABLE:
		if (map->destroyablesHead == nullptr)
		{
			map->destroyablesHead = node;
			map->destroyablesEnd = node;
		}
		else
		{
			map->destroyablesEnd->next = node;
			map->destroyablesEnd = node;
		}
		break;
	case TILE:
		if (map->tilesHead == nullptr)
		{
			map->tilesHead = node;
			map->tilesEnd = node;
		}
		else
		{
			map->tilesEnd->next = node;
			map->tilesEnd = node;
		}
		break;
	}
}

void removeFromMap(GameObject* obj)
{
	obj->toBeDestroyed = true;
}

bool moveLogic(Destroyable* obj, int velX, int velY)
{
	if (velX == 0 && velY == 0)
		return true;

	int centerX = obj->posX + obj->def->width / 2;
	int centerY = obj->posY + obj->def->height / 2;

	int targetX = centerX + velX;
	int targetY = centerY + velY;
	Map* map;
	if (obj->mapId == 0)
		map = &GAME_INSTANCE.ground;
	else
		map = &GAME_INSTANCE.underground;

	int index = ((targetX >> 6) & 0xffff) + ((targetY >> 6) << 16);
	AVLTreeNode *node = search(map->tilesMap, index);
	if (node == nullptr)
	{
		if (velX == 0 || velY == 0)
			return false;
		else
		{
			bool test1 = moveLogic(obj, velX, 0);
			if (test1)
				return true;
			return moveLogic(obj, 0, velY);
		}
	}

	MapTile* tile = (MapTile*)node->value;
	if (!tile->walkable)
	{
		if (velX == 0 || velY == 0)
			return false;
		else
		{
			bool test1 = moveLogic(obj, velX, 0);
			if (test1)
				return true;
			return moveLogic(obj, 0, velY);
		}
	}

	obj->posX += velX;
	obj->posY += velY;
	return true;
}

void playerLogic()
{
	Player* player = GAME_INSTANCE.player;

	Map* map;
	if (player->mapId == 0)
		map = &GAME_INSTANCE.ground;
	else
		map = &GAME_INSTANCE.underground;

	int index = ((player->posX >> 6) & 0xffff) + ((player->posY >> 6) << 16);
	AVLTreeNode* node = search(map->tilesMap, index);
	if (node != nullptr && ((MapTile*)node->value)->def->id == objDefList.gate.id)
	{
		if (player->posX + 32 > 8 && player->posX + 32 < 56 && player->posY + 32 > 8 && player->posY + 32 < 56)
		{
			changeMap();
			return;
		}
	}

	if (player->mapId == 1)
		infiniteGenMap(player->posX, player->posY);

	int frame = player->currentFrame;
	int nextFrame = player->nextFrame;
	
	if (player->tick % player->def->frameLengths[player->currentFrame] == 0)
	{
		if (player->moveStatus == MV_STILL)
		{
			if (frame <= 2)
			{
				player->currentFrame = 1;
				player->nextFrame = 1;
			}
			else if (frame <= 5)
			{
				player->currentFrame = 4;
				player->nextFrame = 4;
			}
			else if (frame <= 8)
			{
				player->currentFrame = 7;
				player->nextFrame = 7;
			}
			else
			{
				player->currentFrame = 10;
				player->nextFrame = 10;
			}
		}
		else {
			player->currentFrame = nextFrame;

			if (nextFrame > frame)
			{
				if (nextFrame % 3 == 1)
					player->nextFrame++;
				else
					player->nextFrame--;
			}
			else
			{
				if (nextFrame % 3 == 1)
					player->nextFrame--;
				else
					player->nextFrame++;
			}

			if(player->moveStatus == MV_UP && frame / 3 != 0) 
			{
				player->currentFrame = 1;
				player->nextFrame = 2;
			}
			if (player->moveStatus == MV_LEFT && frame / 3 != 1)
			{
				player->currentFrame = 4;
				player->nextFrame = 5;
			}
			if (player->moveStatus == MV_DOWN && frame / 3 != 2)
			{
				player->currentFrame = 7;
				player->nextFrame = 8;
			}
			if (player->moveStatus == MV_RIGHT && frame / 3 != 3)
			{
				player->currentFrame = 10;
				player->nextFrame = 11;
			}
		}
	}

	int velX = 0;
	int velY = 0;
	if (controller.wDown)
	{
		velY -= player->speed;
	}
	if (controller.aDown)
	{
		velX -= player->speed;
	}
	if (controller.sDown)
	{
		velY += player->speed;
	}
	if (controller.dDown)
	{
		velX += player->speed;
	}

	moveLogic((Destroyable*)player, velX, velY);

	if (controller.aDown && !controller.dDown)
	{
		player->moveStatus = MV_LEFT;
	}
	else if (controller.dDown && !controller.aDown)
	{
		player->moveStatus = MV_RIGHT;
	}
	else if (controller.wDown && !controller.sDown)
	{
		player->moveStatus = MV_UP;
	}
	else if (controller.sDown && !controller.wDown)
	{
		player->moveStatus = MV_DOWN;
	}
	else
	{
		player->moveStatus = MV_STILL;
	}

	playerAttackLogic();
}

void enemyLogic(Enemy* enemy)
{
	int frame = enemy->currentFrame;
	int nextFrame = enemy->nextFrame;

	if (enemy->tick % enemy->def->frameLengths[enemy->currentFrame] == 0)
	{
		enemy->currentFrame = nextFrame;
		enemy->nextFrame = frame;

		if (enemy->moveStatus == MV_UP && enemy->currentFrame / 2 != 0) {
			enemy->currentFrame = 0;
			enemy->nextFrame = 1;
		}
		if (enemy->moveStatus == MV_LEFT && enemy->currentFrame / 2 != 1) {
			enemy->currentFrame = 2;
			enemy->nextFrame = 3;
		}
		if (enemy->moveStatus == MV_DOWN && enemy->currentFrame / 2 != 2) {
			enemy->currentFrame = 4;
			enemy->nextFrame = 5;
		}
		if (enemy->moveStatus == MV_RIGHT && enemy->currentFrame / 2 != 3) {
			enemy->currentFrame = 6;
			enemy->nextFrame = 7;
		}
	}

	if (enemy->hp <= 0)
	{
		enemy->toBeDestroyed = true;
		if (enemy->mapId == 1)
			GAME_INSTANCE.score++;
		return;
	}

	if (enemy->tick % 10 == 0)
	{
		int deltaX = enemy->posX - GAME_INSTANCE.player->posX;
		int deltaY = enemy->posY - GAME_INSTANCE.player->posY;
		int deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (deltaS < 36)
			GAME_INSTANCE.player->hp -= 5;
	}

	if (enemy->mapId == 0)
	{
		if (enemy->tick % 10 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				int deltaX = enemy->posX - GAME_INSTANCE.towers[i]->posX;
				int deltaY = enemy->posY - GAME_INSTANCE.towers[i]->posY;
				int deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
				if (deltaS < 36)
					GAME_INSTANCE.towers[i]->hp -= 5;
			}
		}

		Tower* target = nullptr;
		for (int i = 0; i < 4; i++)
			if (GAME_INSTANCE.towers[i]->id == enemy->targetId)
				target = GAME_INSTANCE.towers[i];

		int deltaX = target->posX - enemy->posX;
		int deltaY = target->posY - enemy->posY;
		if (deltaX > -36 && deltaX < 36)
			deltaX = 0;
		if (deltaY > -36 && deltaY < 36)
			deltaY = 0;

		int deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (deltaS == 0)
		{
			enemy->moveStatus = MV_STILL;
			return;
		}
		int velX = enemy->speed * deltaX / deltaS;
		int velY = enemy->speed * deltaY / deltaS;
		moveLogic((Destroyable*)enemy, velX, velY);

		int absDeltaX = deltaX > 0 ? deltaX : -deltaX;
		int absDeltaY = deltaY > 0 ? deltaY : -deltaY;

		if (deltaX > 0 && deltaX >= absDeltaY)
			enemy->moveStatus = MV_RIGHT;
		else if (deltaX < 0 && deltaX <= -absDeltaY)
			enemy->moveStatus = MV_LEFT;
		else if (deltaY > 0 && deltaY > absDeltaX)
			enemy->moveStatus = MV_DOWN;
		else if (deltaY < 0 && deltaY < -absDeltaX)
			enemy->moveStatus = MV_UP;
		else
			enemy->moveStatus = MV_STILL;
	}
	else
	{
		if (enemy->tick % 30 == 0)
		{
			enemy->moveStatus = rand() % 5;
		}
		switch (enemy->moveStatus)
		{
		case MV_STILL:
			moveLogic((Destroyable*)enemy, 0, 0);
			break;
		case MV_UP:
			moveLogic((Destroyable*)enemy, 0, -enemy->speed);
			break;
		case MV_LEFT:
			moveLogic((Destroyable*)enemy, -enemy->speed, 0);
			break;
		case MV_DOWN:
			moveLogic((Destroyable*)enemy, 0, enemy->speed);
			break;
		case MV_RIGHT:
			moveLogic((Destroyable*)enemy, enemy->speed, 0);
			break;
		}
	}
}

void playerAttackLogic()
{
	int playerDamage = (sqrt(GAME_INSTANCE.player->level) + 1) * 100;
	if (controller.leftDown && GAME_INSTANCE.player->tick % 10 == 0)
	{
		for (int i = 0; i < GAME_INSTANCE.player->level + 1; i++)
		{
			int deltaX = controller.mouseX - 640 + 32;
			int deltaY = controller.mouseY - 384 + 32;
			double deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);

			double velX = 24.0 * deltaX / deltaS;
			double velY = 24.0 * deltaY / deltaS;
			int bias = GAME_INSTANCE.player->level + 1;
			if (bias > 6)
				bias = 6;
			velX += (rand() / 32767.0 - 0.5) * bias;
			velY += (rand() / 32767.0 - 0.5) * bias;
			GameObject* bullet = createBullet(GAME_INSTANCE.player->posX + 24, GAME_INSTANCE.player->posY + 24, velX, velY, playerDamage);
			if (GAME_INSTANCE.playerOnGround)
				addToMap(&GAME_INSTANCE.ground, bullet, BULLET);
			else
				addToMap(&GAME_INSTANCE.underground, bullet, BULLET);
		}
	}
}

void towerLogic(Tower* tower)
{
	if (tower->tick % 5 == 0 && tower->hp > 0)
	{
		int bulletsLeft = tower->level * sqrt(tower->level) + 1;
		int bulletDamage = (sqrt(tower->level) + 1) * 20;
		List currentDestroyable = GAME_INSTANCE.ground.destroyablesHead;
		while (bulletsLeft > 0 && currentDestroyable != nullptr)
		{
			Destroyable* value = (Destroyable*)currentDestroyable->value;
			if (value->def->id == objDefList.enemy.id)
			{
				int deltaX = value->posX - tower->posX;
				int deltaY = value->posY - tower->posY;
				double deltaS = sqrt(deltaX * deltaX + deltaY * deltaY);
				double velX = deltaX * 24.0 / deltaS;
				double velY = deltaY * 24.0 / deltaS;
				GameObject* bullet = createBullet(tower->posX + 24, tower->posY + 24, velX, velY, bulletDamage);
				addToMap(&GAME_INSTANCE.ground, bullet, BULLET);
				bulletsLeft--;
			}
			currentDestroyable = currentDestroyable->next;
		}
	}

	if (tower->hp <= 0)
	{
		tower->currentFrame = 1;
		tower->nextFrame = 1;
	}
}

void bulletLogic(int mapId, Bullet* bullet)
{
	Map* map;
	if (mapId == 0)
		map = &GAME_INSTANCE.ground;
	else
		map = &GAME_INSTANCE.underground;

	AVLTreeNode* node = search(map->tilesMap, (((bullet->posX + 8) >> 6) & 0xffff) + (((bullet->posY + 8) >> 6) << 16));
	if (node == nullptr || !((MapTile*)node->value)->walkable)
	{
		bullet->toBeDestroyed = true;
		return;
	}

	List currentDestoryable = map->destroyablesHead;
	while (currentDestoryable != nullptr)
	{
		Destroyable* target = (Destroyable*)currentDestoryable->value;
		int deltaX = target->posX - bullet->posX + 24;
		int deltaY = target->posY - bullet->posY + 24;
		if (target->def->id == objDefList.enemy.id && deltaX <= 24 && deltaX >= -24 && deltaY <= 24 && deltaY >= -24)
		{
			target->hp -= bullet->damage;
			bullet->toBeDestroyed = true;
			return;
		}
		currentDestoryable = currentDestoryable->next;
	}

	bullet->posX += bullet->velX;
	bullet->posY += bullet->velY;
}

void coinLogic(Destroyable* coin)
{
	int deltaX = coin->posX - GAME_INSTANCE.player->posX;
	int deltaY = coin->posY - GAME_INSTANCE.player->posY;
	if (deltaX < 16 && deltaX > -16 && deltaY < 16 && deltaY > -16)
	{
		GAME_INSTANCE.player->coins++;
		coin->toBeDestroyed = true;
	}
}

void upgradeLogic()
{
	int mapX = controller.mouseX + GAME_INSTANCE.player->posX - 640 + 32;
	int mapY = controller.mouseY + GAME_INSTANCE.player->posY - 384 + 32;

	int deltaX = mapX - GAME_INSTANCE.player->posX;
	int deltaY = mapY - GAME_INSTANCE.player->posY;

	if (deltaX > 0 && deltaX < 64 && deltaY > 0 && deltaY < 64 && GAME_INSTANCE.player->coins > 0)
	{
		GAME_INSTANCE.player->level++;
		GAME_INSTANCE.player->coins--;
	}

	for (int i = 0; i < 4; i++)
	{
		deltaX = mapX - GAME_INSTANCE.towers[i]->posX;
		deltaY = mapY - GAME_INSTANCE.towers[i]->posY;

		if (deltaX > 0 && deltaX < 64 && deltaY > 0 && deltaY < 64 && GAME_INSTANCE.player->coins > 0)
		{
			GAME_INSTANCE.towers[i]->level++;
			GAME_INSTANCE.player->coins--;
		}
	}
}

void genEnemy()
{
	int enemyAmount = GAME_INSTANCE.globalTick / 720 + 1;
	int enemyHp = (GAME_INSTANCE.globalTick / 9) + 100;
	for (int i = 0; i < enemyAmount; i++)
	{
		int edgeId = rand() % 4;
		int pos = rand() % 1800 - 900;
		GameObject* enemy = nullptr;
		switch (edgeId)
		{
		case 0:
			enemy = createEnemy(-900, pos, enemyHp, 0);
			break;
		case 1:
			enemy = createEnemy(pos, -900, enemyHp, 0);
			break;
		case 2:
			enemy = createEnemy(900, pos, enemyHp, 0);
			break;
		case 3:
			enemy = createEnemy(pos, 900, enemyHp, 0);
			break;
		}
		addToMap(&GAME_INSTANCE.ground, enemy, DESTROYABLE);
	}
}

void changeMap()
{
	Player* temp = (Player*)malloc(sizeof Player);
	*temp = *GAME_INSTANCE.player;
	GAME_INSTANCE.player->toBeDestroyed = true;
	temp->mapId = !(temp->mapId);

	if (temp->mapId == 0)
		addToMap(&GAME_INSTANCE.ground, (GameObject*)temp, DESTROYABLE);
	else
		addToMap(&GAME_INSTANCE.underground, (GameObject*)temp, DESTROYABLE);

	GAME_INSTANCE.player = temp;
	GAME_INSTANCE.playerOnGround = !GAME_INSTANCE.playerOnGround;
	GAME_INSTANCE.player->posX = 0;
	GAME_INSTANCE.player->posY = 128;
}

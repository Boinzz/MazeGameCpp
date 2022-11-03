#pragma once
#include "game_objects.h"

#define BULLET 0
#define DESTROYABLE 1
#define TILE 2
typedef unsigned int ObjType;

GameObjectDef initPlayer();
GameObjectDef initEnemy();
GameObjectDef initWall();
GameObjectDef initGround();
GameObjectDef initTower();

GameObject *createPlayer();
GameObject *createEnemy(int posX, int posY, int hp, int mapId);
GameObject* createTile(int posX, int posY, bool isWall);
GameObject* createTower(int posX, int posY);

void initMap();

void createGround();
void createUnderground();
void infiniteGenMap(int x, int y);

void addToMap(Map* map, GameObject* obj, ObjType type);
void removeFromMap(GameObject* obj);

bool moveLogic(Destroyable* obj, int speedX, int speedY);
void playerLogic();
void enemyLogic(Enemy* enemy);


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

GameObject *createPlayer();
GameObject *createEnemy(int posX, int posY, int hp, int mapId);
GameObject* createTile(int posX, int posY, bool isWall);

void initMap();

void createGround();

void addToMap(Map* map, GameObject* obj, ObjType type);
void removeFromMap(GameObject* obj);

void moveLogic(Destroyable* obj, int speedX, int speedY);
void playerLogic();
void enemyLogic(Enemy* enemy);
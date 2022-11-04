#pragma once

#include "game_objects.h"

struct ObjDefList {
	GameObjectDef player;
	GameObjectDef enemy;
	GameObjectDef tower;
	GameObjectDef wall;
	GameObjectDef ground;
	GameObjectDef bullet;
	GameObjectDef gate;
	GameObjectDef coin;
};

extern ObjDefList objDefList;

void loadGame();

void renderGameObjects(PaintDevice canvas);

void renderGameObject(GameObject* obj, PaintDevice canvas);

void gameLogic();

void mapLogic(Map* map);
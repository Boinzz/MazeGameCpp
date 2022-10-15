#pragma once

#include "windef.h"

typedef int MoveStatus;

#define MV_STILL 0
#define MV_UP 1
#define MV_DOWN 2
#define MV_LEFT 3
#define MV_RIGHT 4

#define EXTENDS

#define GAME_OBJECT_DEF                 \
int             id;                     \
int             width;                  \
int             height;                 \
int             frameCount;             \
int*            frameLengths;           \
Bitmap*         frames;

struct GameObjectDef
{
	GAME_OBJECT_DEF;
};

#define GAME_OBJECT                     \
int             id;                     \
int             posX;                   \
int             posY;                   \
GameObjectDef*  def;                    \
int             currentFrame;           \
bool            toBeDestroyed;

struct GameObject
{
	GAME_OBJECT;
};

#define MAP_TILE EXTENDS GAME_OBJECT    \
bool            walkable;

struct MapTile
{
	MAP_TILE;
};

#define DESTROYABLE EXTENDS GAME_OBJECT \
int             hp;                     \
int             mapId;

struct Destroyable
{
	DESTROYABLE;
};

#define LIVING EXTENDS DESTROYABLE      \
MoveStatus      moveStatus;             \
int             speed;

struct Living
{
	LIVING;
};

#define PLAYER EXTENDS LIVING           \
bool            attacking;              \
int             coins;                  \
int             level;

struct Player
{
	PLAYER;
};

#define ENEMY EXTENDS LIVING            \
int             targetId;

struct Enemy
{
	ENEMY;
};

#define BULLET EXTENDS GAME_OBJECT      \
float           velX;                   \
float           velY;                   \
int             damage;

struct Bullet
{
	BULLET;
};

#define TOWER EXTENDS DESTROYABLE       \
int             level;                  \
int             targetId;

struct Tower
{
	TOWER;
};

struct ListNode
{
	GameObject* value;
	ListNode* next;
};

typedef ListNode* List;

struct Map
{
	List tiles;
	List destroyables;
	List bullets;
};

struct Game
{
	Map ground;
	Map underground;
	bool playerOnGround;
	Player* player;
};

extern Game GAME_INSTANCE;
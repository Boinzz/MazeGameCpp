#define _CRT_SECURE_NO_WARNINGS

#include "game_logic_base.h"
#include "game_logic_middle.h"
#include "game_logic_top.h"

#define TIMER_ID 1
#define FPS 60
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

Controller controller;
static Instance instance;

static RECT COINS_TEXT_RECT = {10, 678, 170, 758};
static RECT COINS_NUM_RECT = {170, 678, 330, 758};
static RECT SCORES_TEXT_RECT = {950, 678, 1110, 758};
static RECT SCORES_NUM_RECT = {1110, 678, 1270, 758};

static String COINS_TEXT = L"Coins:";
static String coinsValue = (String)malloc(32);
static String SCORES_TEXT = L"Scores:";
static String scoresValue = (String)malloc(32);

void onMain(Instance hInstance)
{
	instance = hInstance;
}

void onWindowCreate(Window window)
{
	loadGame();
	SetTimer(window, TIMER_ID, 1000 / FPS, NULL);
}

Bitmap loadBitmap(const String fileName, int width, int height)
{
	return (Bitmap)LoadImage(instance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
}

void unloadBitmap(Bitmap bitmap)
{
	DeleteObject(bitmap);
}

void onTimer(Window window)
{
	gameLogic();
	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	InvalidateRect(window, &rect, TRUE);
}

void onPaint(Window window, PaintDevice device)
{
	PaintDevice canvas = CreateCompatibleDC(device);
	Bitmap bmp = CreateCompatibleBitmap(device, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(canvas, bmp);
	RECT wholeRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	FillRect(canvas, &wholeRect, CreateSolidBrush(RGB(0x80, 0xb0, 0xf0)));
	renderGameObjects(canvas);
	paintText(canvas);
	BitBlt(device, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, canvas, 0, 0, SRCCOPY);
	DeleteDC(canvas);
	DeleteObject(bmp);
}

void onKeyDown(Key key)
{
	switch (key)
	{
	case 'W':
		controller.wDown = true;
		break;
	case 'A':
		controller.aDown = true;
		break;
	case 'S':
		controller.sDown = true;
		break;
	case 'D':
		controller.dDown = true;
		break;
	}
}

void onKeyUp(Key key)
{
	switch (key)
	{
	case 'W':
		controller.wDown = false;
		break;
	case 'A':
		controller.aDown = false;
		break;
	case 'S':
		controller.sDown = false;
		break;
	case 'D':
		controller.dDown = false;
		break;
	}
}

void onMouseDown(bool isLeft)
{
	if (isLeft)
		controller.leftDown = true;
	else
		controller.rightDown = true;
}

void onMouseUp(bool isLeft)
{
	if (isLeft)
		controller.leftDown = false;
	else
	{
		controller.rightDown = false;
		upgradeLogic();
	}
}

void onMouseMove(unsigned lParam)
{
	controller.mouseX = lParam;
	controller.mouseY = lParam >> 16;
}

void paintText(PaintDevice device)
{
	for (int i = 0; i < 32; i++)
	{
		((char*)coinsValue)[i] = 0;
		((char*)scoresValue)[i] = 0;
	}
	_itoa(GAME_INSTANCE.player->coins, (char*)coinsValue, 10);
	_itoa(GAME_INSTANCE.score, (char*)scoresValue, 10);
	DrawText(device, COINS_TEXT, -1, &COINS_TEXT_RECT, DT_BOTTOM | DT_LEFT);
	DrawText(device, coinsValue, -1, &COINS_NUM_RECT, DT_BOTTOM | DT_LEFT);
	DrawText(device, SCORES_TEXT, -1, &SCORES_TEXT_RECT, DT_BOTTOM | DT_LEFT);
	DrawText(device, scoresValue, -1, &SCORES_NUM_RECT, DT_BOTTOM | DT_LEFT);
}


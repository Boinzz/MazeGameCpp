#include "game_logic_base.h"
#include "game_logic_middle.h"

#define TIMER_ID 1
#define FPS 60
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 768

Controller controller;
static Instance instance;


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
	return (Bitmap)LoadImage(instance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
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
	FillRect(canvas, &wholeRect, CreateSolidBrush(RGB(0x80, 0x80, 0x80)));
	renderGameObjects(canvas);
	BitBlt(device, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, canvas, 0, 0, SRCCOPY);
	DeleteDC(canvas);
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
		controller.rightDown = false;
}

void onMouseMove(unsigned lParam)
{
	controller.mouseX = lParam;
	controller.mouseY = lParam >> 16;
}


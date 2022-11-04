#pragma once

#include "windef.h"


//结构体定义
struct Controller
{
	bool wDown;
	bool aDown;
	bool sDown;
	bool dDown;
	bool leftDown;
	bool rightDown;

	unsigned short mouseX;
	unsigned short mouseY;

};

extern Controller controller;

void onMain(Instance hInstance);

void onWindowCreate(Window window);

void onTimer(Window window);

void onPaint(Window window, PaintDevice device);

Bitmap loadBitmap(const String fileName, int width, int height);

void unloadBitmap(Bitmap bitmap);

void onKeyDown(Key key);

void onKeyUp(Key key);

void onMouseDown(bool isLeft);

void onMouseUp(bool isLeft);

void onMouseMove(unsigned lParam);

void paintText(PaintDevice device);
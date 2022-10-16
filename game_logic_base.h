#pragma once

#include "windef.h"

void onMain(Instance hInstance);

void onWindowCreate(Window window);

void onTimer(Window window);

void onPaint(Window window, PaintDevice device);

Bitmap loadBitmap(const String fileName, int width, int height);

void unloadBitmap(Bitmap bitmap);
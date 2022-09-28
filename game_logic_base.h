#pragma once

#include <Windows.h>

//Fuck Windows API!
typedef HWND Window;

void onWindowCreate(Window window);

void onTimer(Window window);
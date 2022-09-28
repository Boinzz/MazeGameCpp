#include "game_logic_base.h"

#define TIMER_ID 1
#define FPS 60

void onWindowCreate(Window window)
{
	SetTimer(window, TIMER_ID, 1000 / FPS, NULL);
}

void onTimer(Window window)
{
	UpdateWindow(window);
}

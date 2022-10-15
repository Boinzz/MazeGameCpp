#pragma once

#include "game_objects.h"

void loadGame();

void renderGameObjects(PaintDevice canvas);

void renderGameObject(GameObject* obj, PaintDevice canvas);
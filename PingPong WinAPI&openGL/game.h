#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/utime.h>
#include "window.h"
#include "drawing.h"
#include "utils.h"
#include "gameObject.h"

struct Game {
	int gameObjectsCount;
	void** gameObjects;
	char* title;
	unsigned long lastFrame;
	int maxFps;
	window* window;
	int userPoints;
	int computerPoints;
};  typedef struct Game Game;


//Built-in functions
void game_init(Game *game);
void game_udpate(Game* game);
void game_draw(Game* game);
void game_destruct(Game* game);

//User functions
void computerMove(Game* game);
int keyboardEvents(Game* game);
int checkBallCollision(gameObjectCircle* obj1, gameObjectRect* obj2);
void checkPoint(Game* game);

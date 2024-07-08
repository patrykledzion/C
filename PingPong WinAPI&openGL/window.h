#pragma once



#define null NULL
#define CLASS_NAME "GameWindowClass"

struct window {
	void* instance;
	int offsetX;
	int offsetY;
	int width;
	int height;
	int keysPressed[0xFF];
}; typedef struct window window;

window* createWindow(int width, int height, char* title);
void updateWindow();
int isWindowOpened(window* window);
void renderFrame(window* window);
void startDraw(window* window);
void endDraw(window* window);


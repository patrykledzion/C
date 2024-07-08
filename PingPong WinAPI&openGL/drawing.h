#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#include <stdio.h>
#include "utils.h"
#include "window.h"
#include "bitmap.h"

#define GL_BGRA 0x80E1
#define TEXTURE_FLAG_ALPHA_BLEND 0b1


void drawTriangle(Vector3_t c1, Vector3_t c2, Vector3_t c3, Color4_t color, window* window);
void drawRect(rect* rectCords, Color4_t* color, rect* textureCords, texture* texture, long depth, window* window);
void drawCircle(long x, long y, long r, int vCount, Color4_t* color, long depth, window* window);
void loadTexture(texture* out, Image* image);
void free_texture(texture* txt);
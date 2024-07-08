#pragma once

#include <stdint.h>

struct texture
{
	uint64_t	pixelWidth;
	uint64_t	pixelHeight;
	uint64_t	flags;
	void*		pointer;
}; typedef struct texture texture;

struct rect
{
	long x;
	long y;
	long w;
	long h;
}; typedef struct rect rect;

struct Color4 {
	float r;
	float g;
	float b;
	float a;
}; typedef struct Color4 Color4_t;

struct Vector3 {
	long x;
	long y;
	long z;
}; typedef struct Vector3 Vector3_t;

struct Vector2 {
	long x;
	long y;
	long z;
}; typedef struct Vector2 Vector2_t;

Vector3_t* Vector3(long x, long y, long z);
Vector2_t* Vector2(long x, long y);
Color4_t* Color4f(float r, float g, float b, float a);


unsigned long deltaTime(int fps);
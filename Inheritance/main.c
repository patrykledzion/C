#include <stdio.h>
#include <stdlib.h>

typedef struct color {
	int r;
	int g;
	int b;
	int a;
} Color;

typedef struct shape {
	float x;
	float y;
	Color color; //(struct color)
} Shape;

typedef struct circle {
	Shape base;
	float r;
} Circle;

typedef struct rectangle {
	Shape base;
	float w;
	float h;
} Rectangle;

typedef struct square {
	Rectangle base;
	float w;
} Square;

Color rgba(int r, int g, int b, int a)
{
	return (Color) { .r = r, .g = g, .b = b, .a = a };
}

Circle* createCircle(float x, float y, float r, Color color)
{
	Circle* c = malloc(sizeof(Circle));
	if (c == NULL)return NULL;
	c->base.color = color;
	c->base.x = x;
	c->base.y = y;
	c->r = r;

	return c;
}

Rectangle* createRect(float x, float y, float w, float h, Color color)
{
	Rectangle* c = malloc(sizeof(Rectangle));
	if (c == NULL)return NULL;
	c->base.color = color;
	c->base.x = x;
	c->base.y = y;
	c->w = w;
	c->h = h;

	return c;
}

Square* createSquare(float x, float y, float w, Color color)
{
	Square* s = malloc(sizeof(Square));
	if (s == NULL)return NULL;
	Rectangle* rect = createRect(x, y, w, w, color);
	s->base = *rect;
	free(rect);
	s->w = w;
	return s;
}

int main()
{
	Square* s = createSquare(1, 2, 3, rgba(7, 3, 1, 2));
	if (s == NULL)return 1;
	int x = 7;
	free(s);
	return 0;
}
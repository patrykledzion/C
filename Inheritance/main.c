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
	void (*print)(struct shape*);
	Color color;
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

void printCircle(Shape* shape)
{
	Circle* t = (Circle*)shape;
	printf("Radius: %f\n", t->r);
	printf("Pos: %f,%f\n", t->base.x, t->base.y);
	printf("Color: (%d, %d, %d, %d)\n",
		t->base.color.r, t->base.color.g, t->base.color.b, t->base.color.a);
}

void printSquare(Shape* shape)
{
	Square* t = (Square*)shape;
	printf("Size: %f\n", t->w);
	printf("Pos: %f,%f\n", t->base.base.x, t->base.base.y);
	printf("Color: (%d, %d, %d, %d)\n",
		t->base.base.color.r, t->base.base.color.g, t->base.base.color.b, t->base.base.color.a);
}

void printRectangle(Shape* shape)
{
	Rectangle* t = (Rectangle*)shape;
	printf("Size: %f x %f\n", t->w, t->h);
	printf("Pos: %f,%f\n", t->base.x, t->base.y);
	printf("Color: (%d, %d, %d, %d)\n",
		t->base.color.r, t->base.color.g, t->base.color.b, t->base.color.a);
}
typedef void (*FuncPtr)(int);
Circle* createCircle(float x, float y, float r, Color color)
{	 
	Circle* c = malloc(sizeof(Circle));
	if (c == NULL)return NULL;
	c->base.color = color;
	c->base.x = x;
	c->base.y = y;
	c->r = r;
	c->base.print = &printCircle;
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
	c->base.print = &printRectangle;
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
	s->base.base.print = &printSquare;
	return s;
}

int main()
{
	Shape *shapes[3];
	shapes[0] =   (Circle*)createCircle(5, 10, 15, rgba(2, 1, 3, 7));
	shapes[1] = (Square*)createSquare(10, 15, 20, rgba(2, 1, 3, 7));
	shapes[2] = (Rectangle*)createRect(10, 15, 20, 25, rgba(2, 1, 3, 7));

	for (int i = 0; i < 3; i++)
	{
		shapes[i]->print(shapes[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		free(shapes[i]);
	}

	return 0;
}

#include "gameObject.h"

gameObjectCircle* createGameObject_circle(long x, long y, long r, long depth, Color4_t* color)
{
	gameObjectCircle* obj = malloc(sizeof(gameObjectCircle));
	if (obj == NULL)return NULL;

	obj->super = malloc(sizeof(gameObject));
	if (obj == NULL)
	{
		free(obj);
		return NULL;
	}

	obj->super->type = GO_CIRCLE;
	obj->super->id = OBJECT_ID;
	obj->super->x = x;
	obj->super->y = y;
	obj->super->color = color;

	obj->r = r;
	obj->depth = depth;
	obj->speedX = 0;
	obj->speedY = 0;

	OBJECT_ID++;

	return obj;
}

gameObjectRect* createGameObject_rect(long x, long y, long w, long h, long depth, Color4_t* color, texture *txt)
{
	gameObjectRect* obj = malloc(sizeof(gameObjectRect));
	if (obj == NULL)return NULL;

	obj->super = malloc(sizeof(gameObject));
	if (obj == NULL)
	{
		free(obj);
		return NULL;
	}

	obj->super->type = GO_RECT;
	obj->super->id = OBJECT_ID;
	obj->super->x = x;
	obj->super->y = y;
	obj->super->color = color;

	obj->w = w;
	obj->h = h;
	obj->depth = depth;
	obj->txt = txt;
	
	OBJECT_ID++;

	return obj;

}

void freeGameObjects(void** gameObjects, int count)
{
	if (gameObjects == NULL)return;
	for (int i = 0; i < count; i++)
	{
		free(gameObjects[i]);
	}
	free(gameObjects);
}

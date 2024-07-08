#include "utils.h"

Vector3_t* Vector3(long x, long y, long z)
{
	Vector3_t ret;
	ret.x = x;
	ret.y = y;
	ret.z = z;
	return &ret;
}

Vector2_t* Vector2(long x, long y)
{
	Vector2_t ret;
	ret.x = x;
	ret.y = y;
	return &ret;
}

Color4_t* Color4f(float r, float g, float b, float a)
{
	Color4_t ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.a = a;
	return &ret;
}

 

unsigned long deltaTime(int fps)
{
	
}

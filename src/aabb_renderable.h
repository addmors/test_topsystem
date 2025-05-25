#pragma once
#include "prim_renderable.h"

class aabb_renderable
	: public prim_renderable
{
public:
	aabb_renderable(const Point& min, const Point& max);
};
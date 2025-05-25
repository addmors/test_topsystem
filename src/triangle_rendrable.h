#pragma once
#include "prim_renderable.h"
#include "point.h"
#include <array>

class triangle_renderable
	: public prim_renderable
{
public:
	triangle_renderable(const Point& p1, const Point& p2, const Point& p3);
};
#include "triangle_rendrable.h"

triangle_renderable::triangle_renderable(const Point& p1, const Point& p2, const Point& p3)
	: prim_renderable({p1, p2, p3})
{
	generateVBOVAO();
}
#include "aabb_renderable.h"

aabb_renderable::aabb_renderable(const Point& min, const Point& max)
	: prim_renderable(
		{ 
			min, 
			Point{ {max.position.x, min.position.y, max.position.z}, min.color},
			max,
			Point{ {min.position.x, max.position.y, max.position.z}, max.color},
		}
	)
{
	generateVBOVAO();
}
#pragma once
#include "prim_renderable.h"
#include "point.h"

class regulal_polygon_renderable
	: public prim_renderable
{
public:
	regulal_polygon_renderable(int count, const glm::vec3& center, float radius, const glm::vec3& color);
};
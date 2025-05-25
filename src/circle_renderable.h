#pragma once
#include "regular_polygon_renderable.h"

class circle_renderable
	: public regulal_polygon_renderable
{
public:
	circle_renderable(const glm::vec3& center, float radius, const glm::vec3& color);
};
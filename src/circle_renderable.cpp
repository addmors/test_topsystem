#include "circle_renderable.h"

circle_renderable::circle_renderable(const glm::vec3& center, float radius, const glm::vec3& color)
	:regulal_polygon_renderable(40, center, radius, color)
{
}

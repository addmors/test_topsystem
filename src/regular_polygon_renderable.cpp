#include "regular_polygon_renderable.h"
#include <glm/gtc/constants.hpp>

regulal_polygon_renderable::regulal_polygon_renderable(int count, const glm::vec3& center, float radius, const glm::vec3& color)
{
	count = std::max(3, count);

	const float theta = glm::pi<float>() / 2.0f - glm::pi<float>() / count;
	const float angleStep = 2.0f * glm::pi<float>() / count;

	m_points.reserve(count + 1);
	m_points.emplace_back(center, color);

	for (int i = count; i >= 0; --i)
	{
		float angle = theta + (float)i * angleStep;
		m_points.emplace_back( glm::vec3{ radius * cos(angle) + center.x, radius * sin(angle) + center.y, center.z }, color);
	}

	generateVBOVAO();
}

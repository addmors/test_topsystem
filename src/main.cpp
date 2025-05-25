#include "triangle_rendrable.h"
#include "regular_polygon_renderable.h"
#include "circle_renderable.h"
#include "aabb_renderable.h"

#include "app.h"

const GLuint WIDTH = 1600, HEIGHT = 1600;

int main(int argc, char* argv[])
{
    app m_app;
    m_app.Init(WIDTH, HEIGHT);

    m_app.add_renderable(std::make_shared<triangle_renderable>(
		Point{ { 0.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} },
        Point{ {-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f} },
        Point{ { 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0f} }
    ));
   
	m_app.add_renderable(std::make_shared<regulal_polygon_renderable>(
		4,
		glm::vec3{ -1.0f, 0.0f, 0.0f },
		0.5f * sqrt(2.0),
		glm::vec3{ 0.0f, 0.0f, 1.0f }
	));


	m_app.add_renderable(std::make_shared<regulal_polygon_renderable>(
		7,
		glm::vec3{ 0.0f, 0.0f, 0.0f },
		0.5f,
		glm::vec3{ 0.0f, 1.0f, 1.0f }
	));


	m_app.add_renderable(std::make_shared<circle_renderable>(
		glm::vec3{ 0.0f, -1.0f, 0.0f },
		0.5f,
		glm::vec3{ 1.0f, 0.0f, 1.0f }
	));

	m_app.add_renderable(std::make_shared<aabb_renderable>(
		Point{ { 0.5f,  0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} },
		Point{ { 2.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 0.0f} }
	));

    m_app.Run();
    return 0;
}
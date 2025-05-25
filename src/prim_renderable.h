#pragma once
#include "renderable.h"
#include "Shader.h"
#include "point.h"

class prim_renderable
	: public renderable
{
public:
	~prim_renderable();
	void render(app*) override;
	void generateVBOVAO();

	bbox get_bbox() override { return { {-1.0f, 1.0f}, {-1.0f, 1.0f}, {-1.0f, 1.0f} }; };
protected:
	prim_renderable();
	prim_renderable(const std::vector<Point>& points);
	prim_renderable(std::vector<Point>&& points);

	std::unique_ptr<Shader> m_Shader;
	GLuint m_VBO = 0, m_VAO = 0;
	std::vector<Point> m_points;
};
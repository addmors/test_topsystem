#pragma once
#include "prim_renderable.h"
#include "app.h"

constexpr std::string_view vertex_code = R"(
#version 420 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 outColor;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
    outColor = aColor;
}

)";

constexpr std::string_view fragment_code = R"(
#version 420 core
in vec3 outColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(outColor, 1.0f);
}
)";

prim_renderable::~prim_renderable()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

prim_renderable::prim_renderable()
	: m_Shader(std::make_unique<Shader>(std::string(vertex_code), std::string(fragment_code)))
{
}

prim_renderable::prim_renderable(std::vector<Point>&& points)
	: m_Shader(std::make_unique<Shader>(std::string(vertex_code), std::string(fragment_code)))
	, m_points(points)
{
}

prim_renderable::prim_renderable(const std::vector<Point>& points)
	: m_Shader(std::make_unique<Shader>(std::string(vertex_code), std::string(fragment_code)))
	, m_points(points)
{
}

void prim_renderable::render(app* _app)
{
	m_Shader->use();
	m_Shader->setMat4("view", _app->get_camera().view_matrix());
	m_Shader->setMat4("projection", _app->get_camera().projection_matrix());

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_points.size());
	glBindVertexArray(0);
}

void prim_renderable::generateVBOVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * m_points.size(), m_points.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

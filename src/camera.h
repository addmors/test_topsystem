#pragma once
#include "bbox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <array>
#include <limits>

class camera
{
public:
	camera();
	const glm::mat4& view_matrix() const { return m_view_matrix; }
	const glm::mat4& projection_matrix() const { return m_proj_matrix; }
	float near() { return m_near; };
	float far() { return m_near + m_z_diff; };
	const glm::vec3& position() const { return m_position; };
	void zoom_to_fit(const bbox& box);

	void OnMouseMove(const glm::ivec2& pos);
	void OnRMouseDown();
	void OnLMouseDown();
	void OnMMouseDown();

	void OnRMouseUp();
	void OnLMouseUp();
	void OnMMouseUp();
	void OnScroll(const glm::dvec2& offsets);

private:
	void produce_rotate(const glm::ivec2& shift);
	void update_view();
	void update_projection();
	void calculate_near_far(const bbox& box);
	std::array<glm::vec3, 8> create_bbox_points(const bbox& box) const;

private:
	glm::quat m_rotation = glm::identity<glm::quat>();

	glm::vec3 m_position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 m_target = glm::vec3(0.0, 0.0, 0.0);
	
	float m_fov = 45.0f;
	float m_aspect = 1.0f;
	float m_near = 0.1f;
	float m_z_diff = 100.f;

	glm::mat4 m_view_matrix = glm::mat4(1);
	glm::mat4 m_proj_matrix = glm::mat4(1);
	bool m_in_drag = false;

	glm::ivec2 m_last_mouse_pos = glm::ivec2(0, 0);
};
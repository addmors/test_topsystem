#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

static constexpr float mouse2angle(int shift)
{
	constexpr float sensitivity = glm::radians(90.0f) / 230.0f;
	return ((float)shift * sensitivity);
}

camera::camera()
{
	update_view();
	update_projection();
}

void camera::zoom_to_fit(const bbox& box) 
{
	m_target = box.get_center();

	const std::array<glm::vec3, 8> points = create_bbox_points(box);
	glm::vec2 min_area = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	glm::vec2 max_area = { -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max() };
	for (const auto& p : points)
	{
		glm::mat4x2 view_mat = m_view_matrix;
		glm::vec2 view_space = view_mat * glm::vec4(p, 1.0);
		min_area = glm::min(min_area, { view_space.x, view_space.y});
		max_area = glm::max(max_area, { view_space.x, view_space.y});
	}

	float distance = glm::length(max_area - min_area) / std::sin(glm::radians(m_fov * 0.5f)) * 0.5;

	glm::mat4 view_rot = glm::mat4(m_rotation);
	m_position = m_target + glm::vec3(view_rot[0][2], view_rot[1][2], view_rot[2][2]) * distance;
	
	update_view();
	calculate_near_far(box);
	update_projection();
	m_bbox = box;
}

void camera::calculate_near_far(const bbox& box) 
{
	const std::array<glm::vec3, 8> points = create_bbox_points(box);

	float min_dist = std::numeric_limits<float>::max();
	float max_dist = -std::numeric_limits<float>::max();

	for (const auto& p : points) 
	{
		glm::vec4 view_space = m_view_matrix * glm::vec4(p, 1.0);
		max_dist = std::max(max_dist, -view_space.z);
		min_dist = std::min(min_dist, -view_space.z);
	}

	float far = 2 * max_dist;
	m_near = std::exp(log(far) - 5);
	m_z_diff = far - m_near;
}

void camera::OnMouseMove(const glm::ivec2& pos)
{
	glm::ivec2 shift = pos - m_last_mouse_pos;
	m_last_mouse_pos = pos;
	if(m_in_drag)
		produce_pan(shift);
}

void camera::OnRMouseDown()
{

}

void camera::OnLMouseDown()
{
	m_in_drag = true;
}

void camera::OnMMouseDown()
{

}

void camera::OnRMouseUp()
{

}

void camera::OnLMouseUp()
{
	m_in_drag = false;
}

void camera::OnMMouseUp()
{

}

void camera::OnScroll(const glm::dvec2& offsets)
{
	m_position += glm::normalize(m_target - m_position) * (glm::length(m_position - m_target) * (float)offsets.y / 50.f);
	update_view();
}

void camera::produce_rotate(const glm::ivec2& shift)
{
	glm::quat modier = glm::identity<glm::quat>();
	modier *= glm::angleAxis(mouse2angle(shift.x), glm::vec3(0, 1, 0)) 
		* glm::angleAxis(mouse2angle(-shift.y), glm::vec3(-1, 0, 0));
	m_rotation = modier * m_rotation;

	glm::mat4 view_rot = glm::mat4(m_rotation);
	m_position = m_target + glm::vec3(view_rot[0][2], view_rot[1][2], view_rot[2][2]) * glm::length(m_position - m_target);
	update_view();
}

void camera::produce_pan(const glm::ivec2& shift)
{
	glm::mat4 view_rot = glm::mat4(m_rotation);
	glm::vec3 up = glm::normalize(glm::vec3(view_rot[0][1], view_rot[1][1], view_rot[2][1]));

	glm::vec3 front = m_target - m_position;
	float length = glm::length(front);
	front = glm::normalize(front);
	glm::vec3 right = glm::normalize(glm::cross(front, up));

	glm::mat4 invVP = glm::inverse(m_proj_matrix * m_view_matrix);

	glm::vec4 deltaNDC = glm::vec4( //TODO
		(-2.0f * shift.x) / 1600.0f,
		(2.0f * shift.y) / 1600.0f,
		0.0f,
		0.0f
	);

	glm::vec4 deltaWorld = invVP * deltaNDC;
	glm::vec3 offset = glm::vec3(deltaWorld) * 2.0f; //TODO

	m_position += offset;
	m_target += offset;
	update_view();
}


void camera::update_view()
{
	glm::mat4 view_rot = glm::mat4(m_rotation);
	glm::vec3 front = glm::vec3(view_rot[0][2], view_rot[1][2], view_rot[2][2]);
	glm::vec3 up = glm::vec3(view_rot[0][1], view_rot[1][1], view_rot[2][1]);

	glm::vec3 const s(normalize(cross(-front, up)));

	m_view_matrix[0][0] = s.x;
	m_view_matrix[1][0] = s.y;
	m_view_matrix[2][0] = s.z;
	m_view_matrix[0][1] = up.x;
	m_view_matrix[1][1] = up.y;
	m_view_matrix[2][1] = up.z;
	m_view_matrix[0][2] = front.x;
	m_view_matrix[1][2] = front.y;
	m_view_matrix[2][2] = front.z;
	m_view_matrix[3][0] = -dot(s, m_position);
	m_view_matrix[3][1] = -dot(up, m_position);
	m_view_matrix[3][2] = -dot(front, m_position);
}

void camera::update_projection()
{
	m_proj_matrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_near + m_z_diff);
}

std::array<glm::vec3, 8> camera::create_bbox_points(const bbox& box) const
{
	return {
		glm::vec3(box.x_min, box.y_min, box.z_min),
		glm::vec3(box.x_max, box.y_min, box.z_min),
		glm::vec3(box.x_min, box.y_max, box.z_min),
		glm::vec3(box.x_max, box.y_max, box.z_min),
		glm::vec3(box.x_min, box.y_min, box.z_max),
		glm::vec3(box.x_max, box.y_min, box.z_max),
		glm::vec3(box.x_min, box.y_max, box.z_max),
		glm::vec3(box.x_max, box.y_max, box.z_max)
	};
}

#pragma once
#include <glm/glm.hpp>

struct bbox
{
	bbox()
		: x_min(0.0f)
		, y_min(0.0f)
		, z_min(0.0f)
		, x_max(0.0f)
		, y_max(0.0f)
		, z_max(0.0f)
	{

	}
    bbox(const glm::vec2& x, const glm::vec2& y, const glm::vec2& z)
		: x_min(x.x)
		, x_max(x.y)
		, y_min(y.x)
		, y_max(y.y)
		, z_min(z.x)
		, z_max(z.y)
    {
    }
 
    glm::vec3 get_center() const
    {
        return { (x_max + x_min) / 2.0f, (y_max + y_min) / 2.0f, (z_max + z_min) / 2.0f };
    }

	void enlarge(const bbox& enlarger)
	{
		if (x_min > enlarger.x_min)	x_min = enlarger.x_min;
		if (x_max < enlarger.x_max)	x_max = enlarger.x_max;
		if (y_min > enlarger.y_min)	y_min = enlarger.y_min;
		if (y_max < enlarger.y_max)	y_max = enlarger.y_max;
		if (z_min > enlarger.z_min)	z_min = enlarger.z_min;
		if (z_max < enlarger.z_max)	z_max = enlarger.z_max;
	}

	float get_diagonal() const
	{
		const float x = x_max - x_min;
		const float y = y_max - y_min;
		const float z = y_max - y_min;
		return x * x + y * y + z * z;
	}
	float operator[](size_t i) const { return box[i]; };
	union
	{
		float box[6];
		struct
		{
			float x_min;
			float x_max;
			float y_min;
			float y_max;
			float z_min;
			float z_max;
		};
	};
    
};
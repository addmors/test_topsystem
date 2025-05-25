#pragma once

class interactive
{
public:
	virtual void OnMouseMove(const glm::ivec2& pos) = 0;
	virtual void OnRMouseDown() = 0;
	virtual void OnLMouseDown() = 0;
	virtual void OnMMouseDown() = 0;

	virtual void OnRMouseUp() = 0;
	virtual void OnLMouseUp() = 0;
	virtual void OnMMouseUp() = 0;

	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	virtual void OnScroll(const glm::dvec2& offsets) = 0;
};
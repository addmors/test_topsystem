#pragma once
#include <memory>
#include "renderable.h"
#include "interactive.h"
#include "camera.h"

struct GLFWwindow;

#define BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);} 

class app
{
public:
	~app();
	void Init(uint16_t width, uint16_t height);
	void Run();
	camera& get_camera();
	void add_renderable(const std::shared_ptr<renderable>& renderable);
	void add_interactive(const std::shared_ptr<interactive>& interactive);
private:
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
	GLFWwindow* m_window = nullptr;
	double deltaTime = 0.0;
	double lastFrame = 0.0;
	camera m_camera;
	std::vector<std::shared_ptr<renderable>> m_renderable;
	std::vector<std::shared_ptr<interactive>> m_interactive;
};
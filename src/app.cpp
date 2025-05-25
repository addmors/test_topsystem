#include "app.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <functional>
#include <unordered_map>

#include "bbox.h"

std::unordered_map<GLFWwindow*, std::function<void(GLFWwindow* window, int key, int scancode, int action, int mode)>> g_app_key_callbacks;
std::unordered_map<GLFWwindow*, std::function<void(GLFWwindow* window, double xpos, double ypos)>> g_app_mouse_callbacks;
std::unordered_map<GLFWwindow*, std::function<void(GLFWwindow* window, int button, int action, int mods)>> g_app_mouse_buttons_callbacks;
std::unordered_map<GLFWwindow*, std::function<void(GLFWwindow* window, double xoffset, double yoffset)>> g_app_scroll_callbacks;

app::~app()
{
	glfwTerminate();
}

void app::Init(uint16_t width, uint16_t height)
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_window = glfwCreateWindow(width, height, "test topsystem", nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	g_app_key_callbacks[m_window] = [this](GLFWwindow* window, int key, int scancode, int action, int mode) { key_callback(window, key, scancode, action, mode); };
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mode) { g_app_key_callbacks[window](window, key, scancode, action, mode); });
	
	g_app_mouse_callbacks[m_window] = [this](GLFWwindow* window, double xpos, double ypos) { mouse_callback(window, xpos, ypos); };
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) { g_app_mouse_callbacks[window](window, xpos, ypos); });

	g_app_scroll_callbacks[m_window] = [this](GLFWwindow* window, double xoffset, double yoffset) { scroll_callback(window, xoffset, yoffset); };
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) { g_app_scroll_callbacks[window](window, xoffset, yoffset); });

	g_app_mouse_buttons_callbacks[m_window] = [this](GLFWwindow* window, int button, int action, int mods) { mouse_button_callback(window, button, action, mods); };
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) { g_app_mouse_buttons_callbacks[window](window, button, action, mods); });

	glewInit();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
}

void app::Run()
{
	if (!m_renderable.empty()) 
	{
		bbox box = m_renderable.at(0)->get_bbox();

		for (const auto& renderable : m_renderable)
			box.enlarge(renderable->get_bbox());

		m_camera.zoom_to_fit(box);
	}

	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_renderable.empty())
			continue;

		for (auto& renderable : m_renderable)
			renderable->render(this);
		
		glfwSwapBuffers(m_window);
	}
}

camera& app::get_camera()
{
	return m_camera;
}

void app::add_renderable(const std::shared_ptr<renderable>& renderable)
{
	m_renderable.push_back(renderable);
}

void app::add_interactive(const std::shared_ptr<interactive>& interactive)
{
	m_interactive.push_back(interactive);
}

void app::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
	{
		for (const auto& interact : m_interactive)
			interact->OnKeyDown(key);
	}
	if (action == GLFW_RELEASE)
	{

		if (key == GLFW_KEY_SPACE)
		{
			if(!m_renderable.empty())
			{
				bbox box = m_renderable.at(0)->get_bbox();

				for (const auto& renderable : m_renderable)
					box.enlarge(renderable->get_bbox());

				m_camera.zoom_to_fit(box);
			}
		}

		for (const auto& interact : m_interactive)
			interact->OnKeyUp(key);
	}
}

void app::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	m_camera.OnMouseMove({ xpos, ypos });
	for (const auto& interact : m_interactive)
		interact->OnMouseMove({ xpos, ypos });
}

void app::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			m_camera.OnMMouseDown();
			for (const auto& interact : m_interactive)
				interact->OnMMouseDown();
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_camera.OnRMouseDown();
			for (const auto& interact : m_interactive)
				interact->OnRMouseDown();
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			m_camera.OnLMouseDown();
			for (const auto& interact : m_interactive)
				interact->OnLMouseDown();
		}
	}

	if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_MIDDLE)
		{
			m_camera.OnMMouseUp();
			for (const auto& interact : m_interactive)
				interact->OnMMouseUp();
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_camera.OnRMouseUp();
			for (const auto& interact : m_interactive)
				interact->OnRMouseUp();
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			m_camera.OnLMouseUp();
			for (const auto& interact : m_interactive)
				interact->OnLMouseUp();
		}
	}
}

void app::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_camera.OnScroll({xoffset, yoffset});
	for (const auto& interact : m_interactive)
		interact->OnScroll({ xoffset, yoffset });
}


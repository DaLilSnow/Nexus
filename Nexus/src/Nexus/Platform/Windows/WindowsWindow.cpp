#include "nxpch.h"
#include "WindowsWindow.h"
#include "Nexus/Core.h"

#include "Nexus/Event/Types/ApplicationEvent.h"
#include "Nexus/Event/Types/KeyEvent.h"
#include "Nexus/Event/Types/MouseEvent.h"

#include <glad/glad.h>

namespace Nexus {

	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error, const char* description) {
		NX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NX_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized) {
			int succes = glfwInit();
			NX_CORE_ASSERT(succes, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NX_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// GLFW Callbacks

		// Window Resize
		glfwSetWindowSizeCallback(m_Window,
			[](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent evt(width, height);
				data.EventCallback(evt);
			}
		);

		// Window Close
		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent evt;
				data.EventCallback(evt);
			}
		);

		// Keys
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent evt(key, 0);
					data.EventCallback(evt);
					break;
				}

				case GLFW_RELEASE: {
					KeyReleasedEvent evt(key);
					data.EventCallback(evt);
					break;
				}

				case GLFW_REPEAT: {
					KeyPressedEvent evt(key, 1);
					data.EventCallback(evt);
					break;
				}
				}

			}
		);

		// Mouse Button
		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent evt(button);
					data.EventCallback(evt);
					break;
				}

				case GLFW_RELEASE: {
					MouseButtonReleasedEvent evt(button);
					data.EventCallback(evt);
					break;
				}
				}

			}
		);

		// Mouse Move
		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xpos, double ypos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent evt((float)xpos, (float)ypos);
				data.EventCallback(evt);
			}
		);

		// Mouse Scroll
		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xoff, double yoff) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent evt((float)xoff, (float)yoff);
				data.EventCallback(evt);
			}
		);

	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

}
#include "nxpch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "Nexus/Application.h"

namespace Nexus {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keyCode) const {
		auto window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const {
		auto window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() const {
		auto window = static_cast<GLFWwindow*>(Application::GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

}

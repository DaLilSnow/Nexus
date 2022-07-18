#include "nxpch.h"
#include "Application.h"

#include "Event/Types/ApplicationEvent.h"
#include "Log/Log.h"

namespace Nexus {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}

}
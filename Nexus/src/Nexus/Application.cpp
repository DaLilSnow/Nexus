#include "nxpch.h"
#include "Application.h"

#include "Event/Types/ApplicationEvent.h"
#include <glad/glad.h>

namespace Nexus {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(NX_BIND_FN(Application::OnEvent));
	}

	Application::~Application() { }

	void Application::OnEvent(Event& evt) {
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(NX_BIND_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(evt);
			if (evt.IsHandled())
				break;
		}
	}

	bool Application::OnWindowClose(const WindowCloseEvent& evt) {
		m_Running = false;
		return false;
	}

	void Application::Run() {
		glClearColor(1, 0, 1, 1);
		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

}
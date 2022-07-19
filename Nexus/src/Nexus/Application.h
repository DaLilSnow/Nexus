#pragma once
#include "nxpch.h"
#include "Window/Window.h"
#include "Nexus/Event/Types/ApplicationEvent.h"
#include "Nexus/Layer/LayerStack.h"

#include <glm/glm.hpp>

namespace Nexus {

	class NEXUS_API Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& evt);

		bool OnWindowClose(const WindowCloseEvent& evt);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		static inline Window& GetWindow() { return *Get().m_Window; }

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}


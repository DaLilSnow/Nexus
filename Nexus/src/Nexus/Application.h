#pragma once
#include "nxpch.h"
#include "Core.h"
#include "Window/Window.h"

namespace Nexus {

	class NEXUS_API Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in client
	Application* CreateApplication();
}


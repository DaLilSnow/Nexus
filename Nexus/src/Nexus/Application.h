#pragma once

#include "Core.h"

namespace Nexus {

	class NEXUS_API Application 
	{
	public:
		Application();
		~Application();

		void Run();

	};

	// To be defined in client
	Application* CreateApplication();
}

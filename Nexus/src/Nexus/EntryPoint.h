#pragma once

#include "Application.h"

#if defined(NX_PLATFORM_WINDOWS)

extern Nexus::Application* Nexus::CreateApplication();

int main(int argc, char** argv) {

	Nexus::Application* app = Nexus::CreateApplication();
	app->Run();
	delete app;

}

#endif
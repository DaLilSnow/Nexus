#pragma once

#include "Application.h"
#include "Log/Log.h"

#if defined(NX_PLATFORM_WINDOWS)

extern Nexus::Application* Nexus::CreateApplication();

int main(int argc, char** argv) {

	Nexus::Log::Init();

	NX_CORE_INFO("Hello World from Nexus");

	Nexus::Application* app = Nexus::CreateApplication();
	app->Run();
	delete app;

}

#endif
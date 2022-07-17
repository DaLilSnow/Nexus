
#include <Nexus.h>

class Sandbox : public Nexus::Application {

public:
	Sandbox() {
		NX_INFO("Hello from {0}!", "Sandbox");
	}

	~Sandbox() {

	}

};

Nexus::Application* Nexus::CreateApplication() {
	return new Sandbox();
}
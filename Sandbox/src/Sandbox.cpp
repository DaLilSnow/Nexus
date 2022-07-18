
#include <Nexus.h>

class ExampleLayer : public Nexus::Layer {
public:
	ExampleLayer() : Layer("Example") { }

	virtual void OnUpdate() override {

	}

	virtual void OnEvent(const Nexus::Event& evt) override {
		if (evt.IsInCategory(Nexus::EventCategory::CategoryInput))
			NX_TRACE("ExampleLayer::OnEvent: {0}", evt);
	}

};

class Sandbox : public Nexus::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}

};

Nexus::Application* Nexus::CreateApplication() {
	return new Sandbox();
}
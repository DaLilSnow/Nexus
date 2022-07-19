#include <Nexus.h>

class ExampleLayer : public Nexus::Layer {
public:
	ExampleLayer() : Layer("Example") { }

	virtual void OnUpdate() override {
		if (Nexus::Input::IsKeyDown(NX_KEY_0))
			NX_INFO("A is pressed");
	}

	virtual void OnEvent(Nexus::Event& evt) override {
		if (evt.IsInCategory(Nexus::EventCategory::CategoryInput))
			NX_TRACE("ExampleLayer::OnEvent: {0}", evt);
	}

};

class Sandbox : public Nexus::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Nexus::GuiLayer());
	}

	~Sandbox() {

	}

};

Nexus::Application* Nexus::CreateApplication() {
	return new Sandbox();
}
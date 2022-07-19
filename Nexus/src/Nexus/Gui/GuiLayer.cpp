#include "nxpch.h"
#include "GuiLayer.h"

#include "Nexus/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Nexus/Application.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nexus {

	GuiLayer::GuiLayer() 
		: Layer("GuiLayer")
	{

	}

	GuiLayer::~GuiLayer() {

	}

	void GuiLayer::OnAttach() {
		ImGui::CreateContext();

		ImGui_ImplOpenGL3_Init("#version 410");
		
		ImGui::StyleColorsDark();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	}

	void GuiLayer::OnUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(
			Application::GetWindow().GetWidth(), 
			Application::GetWindow().GetHeight()
		);

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GuiLayer::OnEvent(Event& evt) {
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowResizeEvent>(NX_BIND_FN(GuiLayer::OnWindowResize));
		dispatcher.Dispatch<KeyPressedEvent>(NX_BIND_FN(GuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(NX_BIND_FN(GuiLayer::OnKeyReleased));
		dispatcher.Dispatch<KeyTypedEvent>(NX_BIND_FN(GuiLayer::OnKeyTyped));
		dispatcher.Dispatch<MouseButtonPressedEvent>(NX_BIND_FN(GuiLayer::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(NX_BIND_FN(GuiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseMovedEvent>(NX_BIND_FN(GuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(NX_BIND_FN(GuiLayer::OnMouseScrolled));
	}

	void GuiLayer::OnDetach() {
		ImGui::DestroyContext();
	}

	bool GuiLayer::OnWindowResize(WindowResizeEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(evt.GetWidth(), evt.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, evt.GetWidth(), evt.GetHeight());
		return false;
	}

	bool GuiLayer::OnKeyPressed(KeyPressedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		//ImGuiKey key = evt.GetKeyCode();
		//NX_CORE_TRACE("{0}", evt);
		//io.AddKeyEvent(key, true);

		io.KeysDown[evt.GetKeyCode()] = true;
		io.KeyAlt = (io.KeysDown[ImGuiKey_LeftAlt] || io.KeysDown[ImGuiKey_RightAlt]);
		io.KeyShift = (io.KeysDown[ImGuiKey_LeftShift] || io.KeysDown[ImGuiKey_RightShift]);
		io.KeyCtrl = (io.KeysDown[ImGuiKey_LeftCtrl] || io.KeysDown[ImGuiKey_RightCtrl]);
		io.KeySuper = (io.KeysDown[ImGuiKey_LeftSuper] || io.KeysDown[ImGuiKey_RightSuper]);

		return false;
	}

	bool GuiLayer::OnKeyReleased(KeyReleasedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		
		io.KeysDown[evt.GetKeyCode()] = false;

		io.KeyAlt = (io.KeysDown[ImGuiKey_LeftAlt] || io.KeysDown[ImGuiKey_RightAlt]);
		io.KeyShift = (io.KeysDown[ImGuiKey_LeftShift] || io.KeysDown[ImGuiKey_RightShift]);
		io.KeyCtrl = (io.KeysDown[ImGuiKey_LeftCtrl] || io.KeysDown[ImGuiKey_RightCtrl]);
		io.KeySuper = (io.KeysDown[ImGuiKey_LeftSuper] || io.KeysDown[ImGuiKey_RightSuper]);

		return false;
	}

	bool GuiLayer::OnKeyTyped(KeyTypedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		int keyCode = evt.GetKeyCode();
		if (keyCode > 0 && keyCode < 0x10000)
			io.AddInputCharacter((unsigned short)keyCode);
		return false;
	}

	bool GuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[evt.GetButton()] = true;
		return false;
	}

	bool GuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[evt.GetButton()] = false;
		return false;
	}

	bool GuiLayer::OnMouseMoved(MouseMovedEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(evt.GetX(), evt.GetY());
		return false;
	}

	bool GuiLayer::OnMouseScrolled(MouseScrolledEvent& evt) const {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel = evt.GetOffsetY();
		io.MouseWheelH = evt.GetOffsetX();

		return false;
	}

}

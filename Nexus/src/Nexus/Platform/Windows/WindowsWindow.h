#pragma once
#include "nxpch.h"

#include "Nexus/Window/Window.h"

#include <GLFW/glfw3.h>

namespace Nexus {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height;  }

		virtual void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return m_Data.VSync; }

		virtual inline void* GetNativeWindow() const { return m_Window; }
	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
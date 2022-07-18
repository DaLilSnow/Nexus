#pragma once
#include "nxpch.h"

#include "Nexus/Event/EventSystem.h"

namespace Nexus {

	struct WindowProps {
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "Nexus Engine",
					unsigned int width = 1280,
					unsigned int height = 720) 
			: Title(title), Width(width), Height(height) { }
	};

	class NEXUS_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() { }

		virtual void OnUpdate() { }

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}
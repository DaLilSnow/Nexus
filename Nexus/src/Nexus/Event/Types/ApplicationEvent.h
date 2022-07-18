#pragma once
#include "nxpch.h"
#include "Nexus/Event/EventSystem.h"

namespace Nexus {

	class NEXUS_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) { }

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(CategoryApplication)

	private:
		const unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() { }

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(CategoryApplication)
	};

}
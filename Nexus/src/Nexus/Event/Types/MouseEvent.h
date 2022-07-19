#pragma once
#include "nxpch.h"
#include "Nexus/Event/EventSystem.h"

namespace Nexus {

	class NEXUS_API MouseButtonEvent : public Event {
	public:
		inline int GetButton() const { return m_Button; }
		
		std::string ToString() const override {
			std::stringstream stream;
			stream << GetName() << ": " << m_Button;
			return stream.str();
		}

	protected:
		MouseButtonEvent(int button) : m_Button(button) { }



		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryMouseButton | CategoryInput)

		const int m_Button;
	};

	class NEXUS_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) { }

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class NEXUS_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) { }

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class NEXUS_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_X(x), m_Y(y) { }

		inline float GetX() { return m_X; }
		inline float GetY() { return m_Y; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseMovedEvent: " << m_X << ", " << m_Y;
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		const float m_X, m_Y;
	};

	class NEXUS_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float offX, float offY) : m_OffX(offX), m_OffY(offY) { }

		inline float GetOffsetX() const { return m_OffX; }
		inline float GetOffsetY() const { return m_OffY; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseScrolledEvent: " << m_OffX << ", " << m_OffY;
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(CategoryMouse | CategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)

	private:
		const float m_OffX, m_OffY;
	};

}
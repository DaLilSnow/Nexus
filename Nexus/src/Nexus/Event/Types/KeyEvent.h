#pragma once
#include "nxpch.h"

#include "Nexus/Event/EventSystem.h"

namespace Nexus {

	class NEXUS_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(CategoryKeyboard | CategoryInput)
	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode) { }

		const int m_KeyCode;
	};

	class NEXUS_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "x)";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount = 0;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) { }

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
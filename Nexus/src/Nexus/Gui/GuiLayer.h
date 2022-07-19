#pragma once
#include "nxpch.h"

#include "Nexus/Layer/Layer.h"
#include "Nexus/Event/Types/ApplicationEvent.h"
#include "Nexus/Event/Types/KeyEvent.h"
#include "Nexus/Event/Types/MouseEvent.h"

namespace Nexus {
	class NEXUS_API GuiLayer : public Layer {
	public:
		GuiLayer();
		~GuiLayer();

		virtual void OnAttach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& evt) override;
		virtual void OnDetach() override;

		bool OnWindowResize(WindowResizeEvent& evt) const;
		bool OnKeyPressed(KeyPressedEvent& evt) const;
		bool OnKeyReleased(KeyReleasedEvent& evt) const;
		bool OnKeyTyped(KeyTypedEvent& evt) const;
		bool OnMouseButtonPressed(MouseButtonPressedEvent& evt) const;
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& evt) const;
		bool OnMouseMoved(MouseMovedEvent& evt) const;
		bool OnMouseScrolled(MouseScrolledEvent& evt) const;

	private:
		float m_Time;
	};
}


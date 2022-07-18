#pragma once

#include "Nexus/Layer/Layer.h"

namespace Nexus {
	class GuiLayer : public Layer {
	public:
		GuiLayer();
		~GuiLayer();

		virtual void OnAttach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(const Event& evt) override;
		virtual void OnDetach() override;
	};
}


#pragma once
#include "nxpch.h"
#include "Nexus/Event/EventSystem.h"

namespace Nexus {

	class NEXUS_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(const Event& evt) { }
		virtual void OnDetach() { }

		virtual void Enable() final { m_Enabled = true; }
		virtual void Disable() final { m_Enabled = false; }

		inline const std::string& GetName() { return m_Name; }

	private:
		std::string m_Name;
		bool m_Enabled = true;
	};

}
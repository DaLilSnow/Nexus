#pragma once
#include "Nexus/Input/Input.h"

namespace Nexus {

	class WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) const override;
		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePosImpl() const override;
	};

}


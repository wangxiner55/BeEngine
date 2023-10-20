#pragma once
#include "../../Engine/Input/Input.h"




namespace BEngine
{
	class WindowInput : public Input
	{

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl()override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	};
}
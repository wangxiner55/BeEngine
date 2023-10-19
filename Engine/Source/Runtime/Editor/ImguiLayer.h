#pragma once
#include "Engine/Layer/Layer.h"


namespace BEngine
{
	class BEAR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(Event& event) override;

	private:
		float m_time = 0.0;
	};
}
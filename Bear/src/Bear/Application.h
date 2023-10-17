#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace BEngine
{
	class BEAR_API Application
	{
	public:

		Application();
		~Application();

		void Run();
	
	private:

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};


	Application* CreateApplication();

}

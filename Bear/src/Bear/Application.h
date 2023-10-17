#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace BEngine
{
	class WindowCloseEvent;
	class BEAR_API Application
	{
	public:

		Application();
		~Application();

		void Run();
	
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};


	Application* CreateApplication();

}

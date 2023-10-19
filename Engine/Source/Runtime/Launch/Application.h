#pragma once
#include "../Core/Base/Core.h"
#include "../Engine/Events/Event.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Layer/LayerStack.h"

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow()  { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}

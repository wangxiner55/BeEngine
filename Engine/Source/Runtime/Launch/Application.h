#pragma once
#include "../Engine/Events/Event.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Layer/LayerStack.h"
#include "../Editor/ImguiLayer.h"
#include "Engine/Render/Buffer.h"
#include "Engine/Render/VertexArray.h"

namespace BEngine
{
	class WindowCloseEvent;
	class Shader;


	class BEAR_API Application
	{
	public:

		Application(const std::string& name = "Bear");
		~Application();

		void Run();
	
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();
		inline Window& GetWindow()  { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		ImGuiLayer* m_ImGuiLayer;

		bool m_Minimized = false;
		bool m_Running = true;
		LayerStack m_LayerStack;
		Ref<Window> m_Window;


		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}

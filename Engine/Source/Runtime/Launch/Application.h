#pragma once
#include "../Engine/Events/Event.h"
#include "../Engine/Window/Window.h"
#include "../Engine/Layer/LayerStack.h"
#include "../Editor/ImguiLayer.h"
#include "Engine/Render/Buffer.h"

namespace BEngine
{
	class WindowCloseEvent;
	class Shader;


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
		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int VBO, VAO, EBO;

		std::unique_ptr<Shader> m_shader;

	private:
		static Application* s_Instance;
	};


	Application* CreateApplication();

}

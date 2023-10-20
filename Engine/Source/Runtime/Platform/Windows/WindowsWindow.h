#pragma once
#include "Engine/Window/Window.h"

#include "GLFW/glfw3.h"

namespace BEngine
{
	class BEAR_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override { return m_Data._width; }
		inline virtual unsigned int GetHeight() const override { return m_Data._height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void* GetNativeWindow() const override { return m_Window; };
		GLFWwindow& GetGLFWwindow() { return *m_Window; }
	
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();


	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string _title;
			unsigned int _width;
			unsigned int _height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

	};


}
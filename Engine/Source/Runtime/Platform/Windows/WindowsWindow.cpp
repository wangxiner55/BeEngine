#include <glad/glad.h>
#include "WindowsWindow.h"
#include "Core/Base/Core.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Platform/OpenGL/Graphics/OpenGLContext.h"

namespace BEngine
{
	static bool s_GLFWInitialized = false;
	static void GLFWErrorINFOCallback(int error, const char* description)
	{
		BR_CORE_ERROR("GLFW Error ({0}) : {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
		
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data._title = props._title;
		m_Data._height = props._height;
		m_Data._width = props._width;

		BR_CORE_INFO("Creating window {0} ({1}, {2})", props._title, props._width, props._height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			BR_CORE_ASSERT(success,"Can not Initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorINFOCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props._width, (int)props._height, props._title.c_str(), nullptr, nullptr);


		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Bind GLFW Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data._height = height;
				data._width = width;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
				
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});


		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});


	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}

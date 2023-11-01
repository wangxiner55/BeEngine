#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace BEngine
{

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

}
#include "RenderCommand.h"


#include "Platform/OpenGL/Graphics/OpenGLRendererAPI.h"
namespace BEngine
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();




}
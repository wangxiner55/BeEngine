#include "RenderCommand.h"


#include "Platform/OpenGL/Graphics/OpenGLRendererAPI.h"
namespace BEngine
{

	RHI* RenderCommand::s_RHI = new OpenGLRendererAPI();




}
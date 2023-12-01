#include "Shader.h"

#include <io.h>
#include "RHI.h"
#include "Render.h"
#include "Platform/OpenGL/Graphics/OpenGLShader.h"

namespace BEngine
{

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fargmentSrc)
	{
		switch (Render::GetAPI())
		{
			case RHI::API::None:		BR_CORE_ASSERT(false, "Shader Renderer::API::None is not supported!");
			case RHI::API::OpenGL:		return CRef<OpenGLShader>(name, vertexSrc, fargmentSrc);
			case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "Shader Renderer::API::Vulkan is not supported!");
			case RHI::API::DX12:		BR_CORE_ASSERT(false, "Shader Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " Shader Unknown RendererAPI ! ");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Render::GetAPI())
		{
		case RHI::API::None:		BR_CORE_ASSERT(false, "Shader Renderer::API::None is not supported!");
		case RHI::API::OpenGL:		return CRef<OpenGLShader>(filepath);
		case RHI::API::Vulkan:		BR_CORE_ASSERT(false, "Shader Renderer::API::Vulkan is not supported!");
		case RHI::API::DX12:		BR_CORE_ASSERT(false, "Shader Renderer::API::DX12 is not supported!");
		}

		BR_CORE_ASSERT(false, " Shader Unknown RendererAPI ! ");
		return nullptr;
	}





	bool ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		if (Exists(name))
		{
			BR_CORE_ASSERT(false, "Shader already exists!");
			return false;
		}
		m_Shaders[name] = shader;
		return true;
	}

	bool ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		if (Exists(name))
		{
			BR_CORE_ASSERT(false, "Shader already exists!");
			return false;
		}
		m_Shaders[name] = shader;
		return true;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;

		
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

	void ShaderLibrary::PreLoad(const std::string& path, const std::string& ext)
	{

		intptr_t file_handle = 0;
		struct _finddata_t file_info;
		std::string temp;
		if ((file_handle = _findfirst(temp.assign(path).append("/*" + ext).c_str(), &file_info)) != -1) {
			do {
				Load(temp.assign(path).append("/").append(file_info.name));
			} while (_findnext(file_handle, &file_info) == 0);
			_findclose(file_handle);
		}
	}

	ShaderLibrary::ShaderLibrary()
	{
		PreLoad("D:/Engine/BeEngine/Engine/Assets/Shader", ".glsl");
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			BR_CORE_ASSERT(false, "Shader already exists!");
			return false;
		}
		return m_Shaders[name];
	}

}
#pragma once
#include "../Component/Component.h"
#include "../../../Resource/AssetData/Model.h"
#include "../../../Render/Shader.h"
#include "../../../Render/Shader.h"

namespace BEngine
{


	struct ModelComponent
	{
		std::string Path = "D:/Engine/Geo/Example/nanosuit.obj";
		Ref<Model> m_Mesh;
		Ref<Shader> m_Shader;
		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent(const std::string& path)
			:Path(path) 
		{
			m_Mesh = CRef<Model>(path);
			m_Shader = ShaderLibrary::GetInstance().Get("Texture");
		}

		ModelComponent(const std::string& path, const Ref<Shader>& shader)
			:Path(path)
		{
			m_Mesh = CRef<Model>(path);
			m_Shader = shader;
		}

		operator std::string() { return Path; }
		operator const std::string() const { return Path; } 

		operator Ref<Shader>() { return m_Shader; }
		operator const Ref<Shader>() { return m_Shader; }


	};



}
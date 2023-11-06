#include "Material.h"


namespace BEngine
{

	Material::Material()
	{
	}

	Material::~Material()
	{
	}

	void Material::SetShader(Ref<Shader>& shader)
	{

		m_Shader-> Unbind();
		m_Shader = shader;
	}

	void Material::SetShader(std::string& filepath)
	{
		Ref<Shader> shader = Shader::Create(filepath);
		m_Shader->~Shader();
		m_Shader = shader;
	}

	void Material::SetTexture(Ref<Texture2D>& texture)
	{
		auto it = std::find(m_Texture2Ds.begin(), m_Texture2Ds.end(), texture);
		if (it != m_Texture2Ds.end()) return;

	}

	void Material::Bind()
	{
		m_Shader->Bind();
	}

	void Material::UnBind()
	{
		m_Shader->Unbind();
	}

}
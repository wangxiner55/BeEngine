#pragma once


#include "../../Render/Shader.h"
#include "../../Render/Texture.h"


namespace BEngine
{

	class Material
	{
	public:
		Material();
		~Material();


		void SetShader(Ref<Shader>& shader);
		void SetShader(std::string& filepath);
		void SetTexture(Ref<Texture2D>& texture);
		//void SetUniformParam();
		void Bind();
		void UnBind();



	private:

		Ref<Shader> m_Shader;
		std::vector<Ref<Texture2D>> m_Texture2Ds;

	};


}
#pragma once


namespace BEngine
{

	class Shader
	{

	public:
		Shader(const std::string& vertexSrc, const std::string& fargmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;


	};


}
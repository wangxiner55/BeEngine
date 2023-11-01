#pragma once

#include "Engine/Render/Shader.h"



namespace BEngine
{

	class OpenGLShader : public Shader
	{

	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fargmentSrc);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();



		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);

		void UploadUniformInt(const std::string& name, const int& value);

		void UploadUniformFloat(const std::string& name, const float& value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void GetFileName(const std::string path);


		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Compile(std::unordered_map<GLenum, std::string>& shaderSources) override;
		virtual std::unordered_map<GLenum, std::string> PreProcess(const std::string& source) override;
		virtual const std::string& GetName() override { return m_Name; }

	private:
		std::string ReadFile(const std::string& filepath);
		uint32_t m_RendererID = -1;
		std::string m_Name = "Standander_Shader";

	};


}
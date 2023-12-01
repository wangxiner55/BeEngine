#pragma once
#include <glad/glad.h>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>




namespace BEngine
{

	class Shader
	{

	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void Compile(std::unordered_map<GLenum, std::string>& shaderSources) = 0;
		virtual std::unordered_map<GLenum, std::string> PreProcess(const std::string& source) = 0;
		virtual const std::string& GetName() = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fargmentSrc);
		static Ref<Shader> Create(const std::string& filepath);


	};




	class ShaderLibrary
	{

	public:
		bool Add(const std::string& name, const Ref<Shader>& shader);
		bool Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;

		static ShaderLibrary& GetInstance()
		{
			//std::call_once(flag, init);
			static ShaderLibrary instance;
			return instance;
		}

		void PreLoad(const std::string& path, const std::string& ext);

		static void Destory()
		{
			ShaderLibrary().~ShaderLibrary();
		}


	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;


		ShaderLibrary();
		~ShaderLibrary() = default;

		ShaderLibrary(const ShaderLibrary&) = delete;
		ShaderLibrary& operator = (const ShaderLibrary&) = delete;

	};

	


}
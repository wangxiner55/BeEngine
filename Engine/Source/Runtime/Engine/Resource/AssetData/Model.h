#pragma once


#include "Engine/Render/Texture.h"
#include "Mesh.h"




namespace BEngine
{

	class Model
	{

	public:
		Model(std::string const& modelpath, bool gamma = false);
		~Model();

		void Load(const std::string& loadpath);
		void Draw(Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));


	private:

		std::vector<Ref<Shader>> m_Shader;
		std::vector<Ref<Texture2D>> m_Texture;
		std::vector<Ref<Mesh>> m_Meshes;

		bool gammaCorrection;

	};









}
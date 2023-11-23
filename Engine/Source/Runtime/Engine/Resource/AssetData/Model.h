#pragma once


#include "Engine/Render/Texture.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace BEngine
{

	class Model
	{

	public:
		Model(std::string const& modelpath, bool gamma = false);
		~Model();

		void Load(const std::string& loadpath);
		void Draw(Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		void processNode(aiNode* node, const aiScene* scene);
		std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType type);
		Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);




	private:

		std::vector<Ref<Shader>> m_Shader;
		std::vector<Ref<Texture2D>> m_Textures_Loaded;
		std::vector<Ref<Mesh>> m_Meshes;

		bool gammaCorrection;
		std::string m_directory;
	};









}
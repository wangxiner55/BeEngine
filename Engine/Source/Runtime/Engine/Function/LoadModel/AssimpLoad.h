#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


namespace BEngine
{
	class AssimpLoad
	{


	public:

		AssimpLoad();
		~AssimpLoad();
		AssimpLoad(std::string& path);

		AssimpLoad(AssimpLoad&&) = delete;
		AssimpLoad(const AssimpLoad&) = delete;
		AssimpLoad& operator=(const AssimpLoad&) = delete;

		void loadModel(std::string& path);
		void processNode(aiNode* node, const aiScene* scene);


	private:

		std::string m_directory;

	};


}
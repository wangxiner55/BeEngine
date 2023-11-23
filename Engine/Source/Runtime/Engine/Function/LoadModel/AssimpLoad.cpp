#include "AssimpLoad.h"

namespace BEngine
{
	AssimpLoad::AssimpLoad()
	{
	}
	AssimpLoad::~AssimpLoad()
	{

	}

	AssimpLoad::AssimpLoad(std::string& path)
	{
		loadModel(path);
	}

	void AssimpLoad::loadModel(std::string& path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			BR_CORE_ERROR("ERROR::ASSIMP::{0}", import.GetErrorString());
			return;
		}
		BR_CORE_INFO("Assimp Load Successful!");
		m_directory = path.substr(0, path.find_last_of('/'));
		
	}



}
#include "Model.h"



namespace BEngine
{
	Model::Model(std::string const& modelpath, bool gamma) 
		: gammaCorrection(gamma)
	{
		Load(modelpath);
	}

	Model::~Model()
	{

	}

	void Model::Load(const std::string& loadpath)
	{

	}

	void Model::Draw(Ref<Shader>& shader, const glm::mat4& transform)
	{
		
		for (uint32_t i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->Draw(shader, transform);
		}
	}

}
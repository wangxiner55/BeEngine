#pragma once
#include <glm/glm.hpp>

namespace BEngine
{

#define MAX_BONE_INFLUENCE 4

	struct Vertex {
		glm::vec3 Position;

		glm::vec3 Normal;
		
		glm::vec2 TexCoords;
		
		glm::vec3 Tangent;

		glm::vec3 Bitangent;

		int m_BoneIDs[MAX_BONE_INFLUENCE];

		float m_Weights[MAX_BONE_INFLUENCE];
	};


	struct TextureDT {
		unsigned int id;
		std::string type;
		std::string path;
	};

	struct MaterialDT {
		unsigned int id;
		std::string type;
		std::string name;
	};



}
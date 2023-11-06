#pragma once
#include <glm/glm.hpp>

namespace BEngine
{

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct TextureDT {
		unsigned int id;
		std::string type;
	};

	struct MaterialDT {
		unsigned int id;
		std::string type;
		std::string name;
	};



}
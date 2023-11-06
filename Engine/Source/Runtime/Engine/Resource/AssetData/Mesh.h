#pragma once
#include <glm/glm.hpp>

namespace BEngine
{



	class MeshData
	{
		MeshData();
		~MeshData();

	public:

		std::vector<Vertex>          vertex_buffer;
		std::vector<unsigned  int>   index_buffer;

	};





}
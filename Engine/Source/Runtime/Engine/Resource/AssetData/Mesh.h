#pragma once
#include <glm/glm.hpp>

namespace BEngine
{

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;



	class Mesh
	{
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<TextureDT>& textures);
		~Mesh();

	public:


		void Draw();

		void SetUpMesh();
	private:

		Ref<VertexArray>			 m_VertexArray;
		Ref<VertexBuffer>			 m_vertexBuffer;
		Ref<IndexBuffer>			 m_indexBuffer;


		std::vector<Vertex>          m_Vertices;
		std::vector<uint32_t>		 m_Indices;
		std::vector<TextureDT>		 m_Textures;




	};





}
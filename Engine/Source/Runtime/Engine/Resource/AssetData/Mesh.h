#pragma once
#include <glm/glm.hpp>
#include "Engine/Render/Shader.h"
#include "../../Render/Texture.h"

namespace BEngine
{

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;



	class Mesh
	{
	public:


		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture2D>>& textures);
		~Mesh();

		void Draw(const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		void SetUpMesh();
	private:

		Ref<VertexArray>			 m_VertexArray;
		Ref<VertexBuffer>			 m_vertexBuffer;
		Ref<IndexBuffer>			 m_indexBuffer;

		std::vector<Vertex>          m_Vertices;
		std::vector<uint32_t>		 m_Indices;
		std::vector<Ref<Texture2D>>	 m_Texture2DS;
	};





}
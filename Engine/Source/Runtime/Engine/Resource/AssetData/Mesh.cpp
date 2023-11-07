#include "Mesh.h"


#include "Engine/Render/VertexArray.h"
#include <glad/glad.h>

namespace BEngine
{

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<TextureDT>& textures)
	{
		this->m_Vertices = vertices;
		this->m_Indices = indices;
		this->m_Textures = textures;


		//m_VertexArray = VertexArray::Create();
		//m_indexBuffer = IndexBuffer::Create();
		//m_vertexBuffer = VertexBuffer::Create();
		//m_VertexArray->AddVertexBuffer()
		//
		//SetUpMesh();
	}

	Mesh::~Mesh()
	{
		
		

	}

	void Mesh::Draw()
	{
		//glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	}

	void Mesh::SetUpMesh()
	{

	}

}
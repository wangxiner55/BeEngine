#include "Mesh.h"


#include "Engine/Render/VertexArray.h"
#include <glad/glad.h>

#include "Engine/Render/Render.h"

namespace BEngine
{

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<TextureDT>& textures)
	{
		this->m_Vertices = vertices;
		this->m_Indices = indices;
		this->m_Textures = textures;


		SetUpMesh();
		
		
	}

	Mesh::~Mesh()
	{
		
		

	}

	void Mesh::Draw(const Ref<Shader>& shader, const glm::mat4& transform )
	{
		Render::Submit(m_VertexArray, shader, transform);
	}

	void Mesh::SetUpMesh()
	{
		m_VertexArray = VertexArray::Create();
		m_indexBuffer = IndexBuffer::Create(m_Indices, m_Indices.size());
		m_vertexBuffer = VertexBuffer::Create(m_Vertices, m_Vertices.size() * sizeof(Vertex));


		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float3, "a_Normal"},
				{ShaderDataType::Float2, "a_UV"},
				{ShaderDataType::Float3, "a_Tangent"},
				{ShaderDataType::Float3, "a_Bitangent"},
				{ShaderDataType::Int4,   "a_BoneID"},
				{ShaderDataType::Float4, "a_Weight"}
			};

			m_vertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_vertexBuffer);
		m_VertexArray->SetIndexBuffer(m_indexBuffer);
	}

}
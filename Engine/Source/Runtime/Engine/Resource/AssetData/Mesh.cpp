#include "Mesh.h"


#include "Engine/Render/VertexArray.h"
#include <glad/glad.h>

#include "../../../Platform/OpenGL/Graphics/OpenGLShader.h"
#include "Engine/Render/Render.h"

namespace BEngine
{

	Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture2D>>& textures)
	{
		this->m_Vertices = vertices;
		this->m_Indices = indices;
		this->m_Texture2DS = textures;


		SetUpMesh();
		
		
	}

	Mesh::~Mesh()
	{
		
		

	}

	void Mesh::Draw(const Ref<Shader>& shader, const glm::mat4& transform )
	{

		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < m_Texture2DS.size(); i++)
		{
			std::string number;
			std::string name;
			switch (m_Texture2DS[i]->GetType())
			{
			case BEngine::TextureType::Diffuse: number = std::to_string(diffuseNr++); name = "diffuse";
				break;
			case BEngine::TextureType::Specular: number = std::to_string(specularNr++); name = "specular";
				break;
			case BEngine::TextureType::Normal: number = std::to_string(normalNr++); name = "normal";
				break;
			case BEngine::TextureType::Height: number = std::to_string(heightNr++); name = "height";
				break;
			default:
				break;
			}
			std::string n = name + number;
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformFloat((name + number), i);
			m_Texture2DS[i]->Bind(i);
		}

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
		m_VertexArray->Unbind();
	}

}
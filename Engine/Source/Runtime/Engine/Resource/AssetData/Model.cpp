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
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(loadpath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			BR_CORE_ERROR("ERROR::ASSIMP::{0}", import.GetErrorString());
			return;
		}
		BR_CORE_INFO("Assimp Load Successful!");
		m_directory = loadpath.substr(0, loadpath.find_last_of('/'));


        BR_CORE_INFO(" MeshNum : {0}", scene->mNumMeshes);
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
        
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
            BR_CORE_INFO(" Mesh: ");
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
           
            m_Meshes.push_back(processMesh(mesh, scene));
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}

	}

    Ref<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
    {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Ref<Texture2D>> textures;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; 

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            


            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;

                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;

                if (mesh->HasTangentsAndBitangents())
                {
                    // tangent
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.Tangent = vector;
                    // bitangent
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.Bitangent = vector;
                }
                else
                {
                    vertex.Tangent = {0,0,0};
                    vertex.Bitangent = {0,0,0};
                }
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        BR_CORE_INFO("texture DIFFUSE num {0}",material->GetTextureCount(aiTextureType_DIFFUSE));
        BR_CORE_INFO("texture SPECULAR num {0}",material->GetTextureCount(aiTextureType_SPECULAR));
        BR_CORE_INFO("texture HEIGHT num {0}",material->GetTextureCount(aiTextureType_HEIGHT));
        BR_CORE_INFO("texture AMBIENT num {0}",material->GetTextureCount(aiTextureType_AMBIENT));

        std::vector<Ref<Texture2D>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Ref<Texture2D>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<Ref<Texture2D>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT);
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        std::vector<Ref<Texture2D>> heightMaps = loadMaterialTextures(material, aiTextureType_NORMALS);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        // return a mesh object created from the extracted mesh data
        return CRef<Mesh>(vertices, indices, textures);
    }


    TextureType GetTypeFormAIType(aiTextureType type)
    {
        switch (type)
        {
        case aiTextureType_NONE:
            break;
        case aiTextureType_DIFFUSE: return TextureType::Diffuse;
            break;
        case aiTextureType_SPECULAR: return TextureType::Specular;
            break;
        case aiTextureType_AMBIENT: 
            break;
        case aiTextureType_EMISSIVE:
            break;
        case aiTextureType_HEIGHT: return TextureType::Height;
            break;
        case aiTextureType_NORMALS: return TextureType::Normal;
            break;
        case aiTextureType_SHININESS:
            break;
        case aiTextureType_OPACITY:
            break;
        case aiTextureType_DISPLACEMENT:
            break;
        case aiTextureType_LIGHTMAP:
            break;
        case aiTextureType_REFLECTION:
            break;
        case aiTextureType_BASE_COLOR:
            break;
        case aiTextureType_NORMAL_CAMERA:
            break;
        case aiTextureType_EMISSION_COLOR:
            break;
        case aiTextureType_METALNESS:
            break;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            break;
        case aiTextureType_AMBIENT_OCCLUSION:
            break;
        case aiTextureType_SHEEN:
            break;
        case aiTextureType_CLEARCOAT:
            break;
        case aiTextureType_TRANSMISSION:
            break;
        case aiTextureType_UNKNOWN:
            break;
        case _aiTextureType_Force32Bit:
            break;
        default:
            break;
        }
    }

    //TODO : Texture Pool
    std::vector <Ref<Texture2D>> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type)
    {
        std::vector<Ref<Texture2D>> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            std::string dir = m_directory + "/" + str.C_Str();
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < m_Textures_Loaded.size(); j++)
            {
                if ((m_Textures_Loaded[j]->GetPath() == dir))
                {
                    textures.push_back(m_Textures_Loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if (!skip)
            {   
                
                Ref<Texture2D> texture = Texture2D::Create(dir);
                texture->SetType(GetTypeFormAIType(type));
                textures.push_back(texture);
                m_Textures_Loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
            }
        }
        return textures;
    }

	void Model::Draw(Ref<Shader>& shader, const glm::mat4& transform)
	{
		
		for (uint32_t i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->Draw(shader, transform);
		}
	}

    void Model::Draw()
    {
    }


}
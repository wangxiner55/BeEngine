#pragma once



#include "../../Render/Texture.h"


namespace BEngine
{

	template<typename T>
	struct LinkData
	{
		std::string name;
		T			type;

	};




	class TextureManager
	{
	public:
		TextureManager();
		~TextureManager();


		//void Add
	private:

		

		//std::vector<Ref<Texture2D>> m_Textures;
		//std::unordered_map<std::string, Ref<Texture2D>> m_Textures;

	};



}
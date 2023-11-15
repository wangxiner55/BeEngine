#pragma once
#include "../../../ThirdParty/TinyObjLoader/include/TinyObjLoader.h"



namespace BEngine
{

	class LoadModel
	{
		enum class LoadMode
		{
			TinyObjLoader = 0, Assimp
		};


		struct LoadAttri
		{
			LoadMode loadMode = LoadMode::TinyObjLoader;



		};


	public:

		LoadModel(const std::string& loadpath);
		~LoadModel();



		//std::string 


	private:

		LoadAttri loadAttri;


	};





}
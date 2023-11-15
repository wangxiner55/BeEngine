#pragma once

#include "TinyObjLoader.h"
#include "Load.h"


namespace BEngine
{

	class TinyLoad //: public Load
	{

	public:

		TinyLoad();


		TinyLoad(const std::string path);

		virtual ~TinyLoad();
		

		void GetPath(std::string path);

		virtual void LoadModel();//override;


	private:

		tinyobj::attrib_t attrib; 
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		std::string warn;
		std::string err;

		bool triangulate = true;


		const char* filename;
		const char* basepath;



	};


	//REGISTER_MESSAGE(TinyLoad, "TinyLoad");

}
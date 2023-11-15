#pragma once

#include <TinyObjLoader.h>

namespace BEngine
{
	class TLoad
	{
	public:


		TLoad();


		TLoad(const std::string& path);

		void GetPath(std::string path);

		void LoadModel(std::string path);//override;


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


}
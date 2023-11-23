#include "TLoad.h"
#include <filesystem>
namespace fs = std::filesystem;

namespace BEngine
{



	TLoad::TLoad()
	{
	}

	TLoad::TLoad(const std::string& path)
	{
		LoadModel(path);
	}

	void TLoad::LoadModel(std::string path)
	{

		std::size_t pos = path.find_last_of("/\\"); 
		std::string sfilename = path; 
		std::string sbasepath = path.substr(0, pos + 1); 
		filename = sfilename.c_str(); 
		basepath = sbasepath.c_str(); 


		bool b_read = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, basepath, triangulate);


		if (!warn.empty())
			BR_CORE_ERROR("warn : {0}", warn);

		if (!err.empty())
			BR_CORE_ERROR("err: {0}", err);

		if (!b_read)
		{
			BR_CORE_ERROR("��ȡobj�ļ�ʧ�ܣ�{0}", filename);
		}
		else
		{
			BR_CORE_INFO("TinyObject Load Obj Successful! ");
			BR_CORE_INFO("��������{}", attrib.vertices.size() / 3);
			BR_CORE_INFO("��������{}", attrib.normals.size() / 3);
			BR_CORE_INFO("UV����{}", attrib.texcoords.size() / 2);
			BR_CORE_INFO("��ģ������{}", shapes.size());
			BR_CORE_INFO("��������{}", materials.size());
		}


	}

}
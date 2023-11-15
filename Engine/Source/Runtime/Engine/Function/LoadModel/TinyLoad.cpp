#include <filesystem>
#include "TinyLoad.h"


namespace fs = std::filesystem;


namespace BEngine
{
	TinyLoad::TinyLoad()
	{
		//const std::string path = "D:Engine/Geo/Box.obj";
		//TinyLoad(path);


	}

	TinyLoad::TinyLoad(const std::string path)
	{
		GetPath(path);
		LoadModel();
		
	}

	TinyLoad::~TinyLoad()
	{
	}

	void TinyLoad::GetPath(std::string path)
	{
		BR_CORE_INFO(path);
		fs::path p = path;
		p.remove_filename();
		
		filename = path.c_str();
		path = p.string();
		basepath = path.c_str();

		BR_CORE_INFO(basepath);
	}

	void TinyLoad::LoadModel()
	{
		bool b_read = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, basepath, triangulate);



		if (!warn.empty())
			BR_CORE_ERROR("warn : {0}", warn);

		if (!err.empty())
			BR_CORE_ERROR("err: {0}",err);

		if (!b_read)
		{
			BR_CORE_ERROR("读取obj文件失败：{0}", filename);
		}
		else
		{

			BR_CORE_INFO("顶点数：{}",		attrib.vertices.size() / 3);
			BR_CORE_INFO("法线数：{}",		attrib.normals.size() / 3);
			BR_CORE_INFO("UV数：{}",		attrib.texcoords.size() / 2);
			BR_CORE_INFO("子模型数：{}",	shapes.size());
			BR_CORE_INFO("材质数：{}",		materials.size());
		}



	}

}
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

		std::size_t pos = path.find_last_of("/\\"); // 找到最后一个/或\的位置
		std::string sfilename = path; // 提取出文件名
		std::string sbasepath = path.substr(0, pos + 1); // 提取出基本路径
		filename = sfilename.c_str(); // 将文件名转为const char*
		basepath = sbasepath.c_str(); // 将基本路径转为const char*


		bool b_read = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, basepath, triangulate);


		if (!warn.empty())
			BR_CORE_ERROR("warn : {0}", warn);

		if (!err.empty())
			BR_CORE_ERROR("err: {0}", err);

		if (!b_read)
		{
			BR_CORE_ERROR("读取obj文件失败：{0}", filename);
		}
		else
		{
			BR_CORE_INFO("TinyObject Load Obj Successful! ");
			BR_CORE_INFO("顶点数：{}", attrib.vertices.size() / 3);
			BR_CORE_INFO("法线数：{}", attrib.normals.size() / 3);
			BR_CORE_INFO("UV数：{}", attrib.texcoords.size() / 2);
			BR_CORE_INFO("子模型数：{}", shapes.size());
			BR_CORE_INFO("材质数：{}", materials.size());
		}


	}

}
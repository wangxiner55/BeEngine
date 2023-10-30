#include "Camera.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"


namespace BEngine
{

	std::shared_ptr<Camera> BEngine::Camera::Create(CameraType type)
	{
		switch (type)
		{
		case BEngine::CameraType::OrthographicCamera: return std::make_shared<OrthographicCamera>();

		case BEngine::CameraType::PerspectiveCamera: return std::make_shared<PerspectiveCamera>();

		default: return std::make_shared<PerspectiveCamera>();

		}

	}



}

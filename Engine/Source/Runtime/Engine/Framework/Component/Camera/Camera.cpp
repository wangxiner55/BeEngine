#include "Camera.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"


namespace BEngine
{

	Ref<Camera> BEngine::Camera::Create(CameraType type)
	{
		switch (type)
		{
		case BEngine::CameraType::OrthographicCamera: return CRef<OrthographicCamera>();

		case BEngine::CameraType::PerspectiveCamera: return CRef<PerspectiveCamera>();

		default: return CRef<PerspectiveCamera>();

		}

	}



}

#pragma once



#include "Camera.h"


namespace BEngine
{

	class CameraManager
	{
		CameraManager();
		~CameraManager();


		Ref<Camera> CreateCamera();
		Ref<Camera> GetCamera();


		void DeleteCamera();


	private:


		std::vector<Ref<Camera>> CurrentViewportCamera;

		
	};








}
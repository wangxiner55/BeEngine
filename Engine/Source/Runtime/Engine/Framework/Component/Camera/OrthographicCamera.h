#pragma once
#include <glm/glm.hpp>
#include "Camera.h"
namespace BEngine
{

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera();

		OrthographicCamera(float left, float right, float bottom, float top);

		virtual void SetPosition(const glm::vec3& position) {
			m_Position = position; 
			RecalculateViewMatrix();
		}
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) {
			m_RotationSpeed = rotation; 
			RecalculateViewMatrix();
		}

		virtual void OnEvent(Event& event) override;
		virtual Ref<void> GetCurrentCamera() override;
	private:
		void RecalculateViewMatrix();
		bool OnKeyPressedEvent(KeyPressedEvent& event);





	};








}
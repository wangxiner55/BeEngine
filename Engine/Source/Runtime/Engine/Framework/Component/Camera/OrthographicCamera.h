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


		virtual void UpdateModelMatrix() override;
		virtual void UpdateViewMatrix() override;
		virtual void UpdateProjectMatrix() override;
		//virtual void OnResize(const float& width, const float& height) override;
		virtual void SetPosition(const glm::vec3& position) {
			m_CameraPosition = position;
			RecalculateViewMatrix();
		}
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) {
			m_RotationSpeed = rotation; 
			RecalculateViewMatrix();
		}

		virtual void OnEvent(Event& event) override;
		virtual Ref<void> GetCurrentCamera() override;
		virtual void ResetProjection(float aspect) override;
	private:
	private:
		void RecalculateViewMatrix();
		bool OnKeyPressedEvent(KeyPressedEvent& event);





	};








}
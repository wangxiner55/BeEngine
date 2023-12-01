#pragma once
#include <glm/glm.hpp>


#include "Camera.h"

namespace BEngine
{
	class KeyPressedEvent;

	class PerspectiveCamera : public Camera
	{
	public:

		PerspectiveCamera();

		virtual void SetPosition(const glm::vec3& position) override {
			m_CameraPosition = position;
		}
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) override {
			m_RotationSpeed = rotation;
			m_CameraRotationVector = rotationVector;
		}

		virtual void Tick(Timestep ts) override;
		virtual Ref<void> GetCurrentCamera() override;
		virtual void OnEvent(Event& event) override;

		virtual void UpdateModelMatrix() override;
		virtual void UpdateViewMatrix() override;
		virtual void UpdateProjectMatrix() override;

		void UpdateProjection(float fov, float width, float height, float Z_near, float Z_far);
		void UpdateProjection(float fov, float aspect, float Z_near = 0.1, float Z_far = 100);
		virtual void ResetProjection(float aspect) override;
	private:


		void updateCameraVectors();

		void UpdateView();

		void UpdateVPMatrix();

		void SetModel();

		void RotationAroundPoint(glm::vec3 rotatepoint, float angle, glm::vec3 rotatorvector);


		// event bind
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnMouseMovementEvent(MouseMovedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnMouseScrollEvent(MouseScrolledEvent& event);



		std::pair<float, float> lastMousePosition = {0,0};

	};







}
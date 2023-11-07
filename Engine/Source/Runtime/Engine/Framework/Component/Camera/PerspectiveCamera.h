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

		const glm::vec3& GetPosition() const { return m_Position; }
		const float& GetRotation()const { return m_RotationSpeed; }
		virtual void SetPosition(const glm::vec3& position) override {
			m_Position = position;
			RecalculateViewMatrix();
		}
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) override {
			m_RotationSpeed = rotation;
			m_RotationVector = rotationVector;
			RecalculateViewMatrix();
		}

		void SetIsFirstMove(bool isMove);

		virtual void OnResize(const float& width, const float& height) override;
		virtual void Tick(Timestep ts) override;
		virtual Ref<void> GetCurrentCamera() override;
		virtual void OnEvent(Event& event) override;
		void UpdataProjectionMatrix(float fov, float width, float height);
	private:



		void SetProjection(float fov, float width, float height, float Z_near = 0.1, float Z_far = 100);
		void SetProjection(float fov, float aspect, float Z_near = 0.1, float Z_far = 100);

		void SetView();

		void SetModel();

		void Update();



		glm::vec3 m_CameraPosition;
		glm::vec3 m_CameraFront;
		glm::vec3 m_CameraUp;



		float m_fov;
		float m_width;
		float m_height;
		float m_Z_near;
		float m_Z_far;
		float aspect;

		// event bind
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnMouseMovementEvent(MouseMovedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnMouseScrollEvent(MouseScrolledEvent& event);

		void RecalculateViewMatrix();
		void UpdataMVPMatrix();
		void UpdataViewMatrix();

		bool isFistMove;
		bool bChanged;


		float offsetX = 0.0;
		float offsetY = 0.0;

		float deltaTime = 0;

		std::pair<float, float> lastMousePosition = {0,0};

	};







}
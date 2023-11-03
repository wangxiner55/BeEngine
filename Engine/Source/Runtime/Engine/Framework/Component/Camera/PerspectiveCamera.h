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

		virtual void Tick(Timestep ts) override;
		virtual Ref<void> GetCurrentCamera() override;
		virtual void OnEvent(Event& event) override;
		void UpdataProjectionMatrix(float fov, float width, float height);
	private:

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
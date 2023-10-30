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
		const float& GetRotation()const { return m_Rotation; }
		virtual void SetPosition(const glm::vec3& position) override {
			m_Position = position;
			RecalculateViewMatrix();
		}
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) override {
			m_Rotation = rotation;
			m_RotationVector = rotationVector;
			RecalculateViewMatrix();
		}


		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetMVMatrix() const { return m_MVMatrix; }
		const glm::mat4& GetMVPMatrix() const { return m_MVPMatrix; }

		virtual void OnEvent(Event& event) override;
	private:

		bool OnKeyPressedEvent(KeyPressedEvent& event);
		void RecalculateViewMatrix();


	};







}
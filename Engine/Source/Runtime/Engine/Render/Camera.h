#pragma once
#include <glm/glm.hpp>

#include "Engine/Input/KeyCodes.h"

#include "Engine/Events/Event.h"
#include "Engine/Events/KeyEvent.h"




namespace BEngine
{
	enum class CameraType
	{
		OrthographicCamera = 0, PerspectiveCamera
	};

	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};


	class Camera
	{
	public:

		virtual ~Camera() {}

		static std::shared_ptr<Camera> Create(CameraType type);


		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) = 0;

		virtual const glm::vec3& GetPosition() { return m_Position; }
		virtual const float& GetRotation() { return m_Rotation; }

		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectMatrix() const { return m_ProjectionMatrix; }

		const glm::mat4& GetMVMatrix() const { return m_MVMatrix; }
		const glm::mat4& GetMVPMatrix() const { return m_MVPMatrix; }


		virtual void OnEvent(Event& event) = 0;
		virtual void RecalculateViewMatrix() = 0;
		void Tick() { RecalculateViewMatrix(); };

	protected:

		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		glm::mat4 m_MVMatrix = glm::mat4(1.0f);
		glm::mat4 m_MVPMatrix = glm::mat4(1.0f);

		glm::vec3 m_Scale = { 1.f, 1.f, 1.0f };
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_RotationVector = { 0.f, 0.f, 1.0f };

		float m_Rotation = 0.0f;
		float m_moveSpeed = 0.1f;
		


		CameraType cameraType = CameraType::PerspectiveCamera;

	};




}
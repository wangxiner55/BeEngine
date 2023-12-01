#pragma once
#include <glm/glm.hpp>

#include "Engine/Input/KeyCodes.h"

#include "Engine/Events/Event.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Input/Input.h"





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

		Camera(float DeltaT = 0.0f) :m_deltaT(DeltaT) {}
		virtual ~Camera() {}

		static Ref<Camera> Create(CameraType type);


		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(float rotation, glm::vec3 rotationVector = glm::vec3(0.0f, 0.0f, 1.0f)) = 0;
		//virtual void OnResize(const float& width, const float& height) = 0;

		virtual const glm::vec3& GetPosition() { return m_CameraPosition; }
		virtual const glm::vec3& GetCameraFront() { return m_CameraFront; }
		virtual const glm::vec3& GetCameraUp() { return m_CameraUp; }
		virtual const glm::vec3& GetCameraRight() { return m_CameraRight; }
		virtual const glm::vec3& GetCameraYawPitch() { return glm::vec3(m_yaw,m_pitch,0); }
		virtual const float& GetRotation() { return m_RotationSpeed; }

		const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetProjectMatrix() const { return m_ProjectionMatrix; }

		const glm::mat4& GetMVMatrix() const { return m_MVMatrix; }
		const glm::mat4& GetVPMatrix() const { return m_VPMatrix; }
		const glm::mat4& GetMVPMatrix() const { return m_MVPMatrix; }

		virtual float& GetRotationSpeed() { return m_RotationSpeed; }
		virtual float& GetMovementSpeed() { return m_moveSpeed; }


		virtual void UpdateModelMatrix() = 0;
		virtual void UpdateViewMatrix() = 0;
		virtual void UpdateProjectMatrix() = 0;

		virtual void ResetProjection( float aspect) = 0;

		virtual Ref<void> GetCurrentCamera() = 0;
		virtual void OnEvent(Event& event) = 0;
		virtual void Tick(Timestep ts) { };



	protected:

		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

		glm::mat4 m_MVMatrix = glm::mat4(1.0f);
		glm::mat4 m_MVPMatrix = glm::mat4(1.0f);
		glm::mat4 m_VPMatrix = glm::mat4(1.0f);


		glm::vec3 m_CameraRotationVector = { 0.f, 0.f, 1.0f };
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 20.0f, 20.0f);
		glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_CameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		float m_fov = 45.0;
		float m_width = 1280.0;
		float m_height = 720.0;
		float m_Z_near = 0.1;
		float m_Z_far = 100.0;
		float m_aspect = 1280.0 / 720.0;

		float m_yaw = -90.0f;
		float m_pitch = -30.0f;
		float m_movespeed = 2.5f;
		float m_sensitity = 0.1f;


		float m_RotationSpeed = 200.0f;
		float m_moveSpeed = 400.0f;
		
		float m_deltaT = 0.0f;


		CameraType cameraType = CameraType::PerspectiveCamera;

	};




}
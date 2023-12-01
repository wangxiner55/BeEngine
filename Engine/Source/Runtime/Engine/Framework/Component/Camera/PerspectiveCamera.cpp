#include "PerspectiveCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/Input/MouseButtonCodes.h"




namespace BEngine
{

	PerspectiveCamera::PerspectiveCamera()
	{
		updateCameraVectors();
		UpdateProjection(m_fov, m_aspect);
		UpdateView();
		UpdateVPMatrix();
	}

	void PerspectiveCamera::Tick(Timestep ts)
	{
		Camera::Tick(ts);
		m_deltaT = (float)ts;
		updateCameraVectors();

		UpdateProjection(m_fov, m_aspect);
		UpdateView();
		UpdateVPMatrix();
	}

	void PerspectiveCamera::UpdateProjection(float m_fov, float width, float height, float Z_near, float Z_far)
	{
		m_fov = m_fov;
		m_width = width;
		m_height = height;
		m_Z_near = Z_near;
		m_Z_far = Z_far;
		m_ProjectionMatrix = glm::perspective(glm::radians((m_fov)), width / height, Z_near, Z_far);
	}

	void PerspectiveCamera::UpdateProjection(float m_fov, float aspect, float Z_near, float Z_far)
	{
		m_fov = m_fov;
		m_aspect = aspect;
		m_Z_near = Z_near;
		m_Z_far = Z_far;
		m_ProjectionMatrix = glm::perspective(glm::radians(m_fov), aspect, Z_near, Z_far);
	}

	void PerspectiveCamera::ResetProjection(float aspect)
	{
		UpdateProjection(m_fov, aspect);
	}

	void PerspectiveCamera::UpdateView()
	{
		m_ViewMatrix = glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
	}

	void PerspectiveCamera::UpdateVPMatrix()
	{
		m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void PerspectiveCamera::SetModel()
	{

	}

	void PerspectiveCamera::RotationAroundPoint(glm::vec3 rotatepoint, float angle, glm::vec3 rotatorvector)
	{
		glm::mat4 trans = glm::mat4(1);
		glm::mat4 InvertTrans = glm::mat4(1);

		if (rotatepoint != glm::vec3(0))
		{
			glm::mat4 trans = glm::translate(glm::mat4(1), -rotatepoint);
			glm::mat4 InvertTrans = glm::translate(glm::mat4(1), rotatepoint);

		}
		glm::mat4 rot = glm::rotate(glm::mat4(1), angle, rotatorvector);

		glm::vec4 pos = InvertTrans * rot * trans * glm::vec4(m_CameraPosition, 1.0);
		m_CameraPosition = glm::vec3(pos.x,pos.y,pos.z);
		m_CameraFront = glm::normalize(-m_CameraPosition);

		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));

		//m_yaw = glm::dot(m_CameraFront, glm::vec3(1., 0., 0.0));
		//m_pitch = glm::dot(m_CameraUp, glm::vec3(0., 1., 0.0));
	}

	void PerspectiveCamera::UpdateModelMatrix()
	{

	}

	void PerspectiveCamera::UpdateViewMatrix()
	{
		UpdateView();
	}

	void PerspectiveCamera::UpdateProjectMatrix()
	{
		UpdateProjection(m_fov, m_aspect);
	}



	Ref<void> PerspectiveCamera::GetCurrentCamera()
	{
		return nullptr;
	}

	//event
	void PerspectiveCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EVENT_BIND(PerspectiveCamera::OnKeyPressedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(EVENT_BIND(PerspectiveCamera::OnMouseMovementEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(EVENT_BIND(PerspectiveCamera::OnMouseScrollEvent));
		dispatcher.Dispatch<WindowResizeEvent>(EVENT_BIND(PerspectiveCamera::OnWindowResizeEvent));

	}



	bool PerspectiveCamera::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == BR_KEY_LEFT || Input::IsKeyPressed(BR_KEY_A))
		{
			m_CameraPosition -= m_CameraRight * m_moveSpeed * m_deltaT;
		}
		if (event.GetKeyCode() == BR_KEY_RIGHT || Input::IsKeyPressed(BR_KEY_D))
		{
			m_CameraPosition += m_CameraRight * m_moveSpeed * m_deltaT;
		}
		if (event.GetKeyCode() == BR_KEY_DOWN || Input::IsKeyPressed(BR_KEY_S))
		{
			m_CameraPosition -= m_CameraFront * m_moveSpeed * m_deltaT;
		}
		if (event.GetKeyCode() == BR_KEY_UP || Input::IsKeyPressed(BR_KEY_W))
		{
			m_CameraPosition += m_CameraFront * m_moveSpeed * m_deltaT;
		}
		if (Input::IsKeyPressed(BR_KEY_Q))
		{
			m_CameraPosition -= m_CameraUp * m_moveSpeed * m_deltaT;
		}
		if (Input::IsKeyPressed(BR_KEY_E))
		{
			m_CameraPosition += m_CameraUp * m_moveSpeed * m_deltaT;
		}
		return false;
	}

	bool PerspectiveCamera::OnMouseMovementEvent(MouseMovedEvent& event)
	{
		if (Input::IsMouseButtonPressed(BR_MOUSE_BUTTON_RIGHT))
		{
			float doffsetX = event.GetX() - lastMousePosition.first;
			float doffsetY = lastMousePosition.second - event.GetY();
			m_yaw += doffsetX * m_deltaT * m_RotationSpeed;
			m_pitch += doffsetY * m_deltaT * m_RotationSpeed;

			/*if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;*/

			updateCameraVectors();
		}

		if (Input::IsMouseButtonPressed(BR_MOUSE_BUTTON_LEFT))
		{
			//float doffsetX = event.GetX() - lastMousePosition.first;
			//float doffsetY = lastMousePosition.second - event.GetY();
			//float angle = glm::sqrt(doffsetX * doffsetX + doffsetY * doffsetY);
			//m_yaw -= doffsetX * m_deltaT * m_RotationSpeed;
			//m_pitch -= doffsetY * m_deltaT * m_RotationSpeed;
			///*if (m_pitch > 89.0f)
			//	m_pitch = 89.0f;
			//if (m_pitch < -89.0f)
			//	m_pitch = -89.0f;*/
			//glm::vec3 dir = glm::normalize(glm::vec3(doffsetY, doffsetX, 0));

			//RotationAroundPoint(glm::vec3(0), glm::radians(angle), -dir);
		}

		lastMousePosition.first = event.GetX();
		lastMousePosition.second = event.GetY();
		return false;
	}

	bool PerspectiveCamera::OnWindowResizeEvent(WindowResizeEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0) 
			return false;
		UpdateProjection((float)m_fov, (float)event.GetWidth(), (float)event.GetHeight(), 0.1, 100);
		return false;
	}

	bool PerspectiveCamera::OnMouseScrollEvent(MouseScrolledEvent& event)
	{
		if (m_fov >= 1.0f && m_fov <= 45.0f)
			m_fov -= event.GetYOffset(); 
		if (m_fov <= 1.0f)
			m_fov = 1.0f; 
		if (m_fov >= 45.0f)
			m_fov = 45.0f; 
		return false;
	}



	void PerspectiveCamera::updateCameraVectors()
	{

		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_CameraFront = glm::normalize(front);

		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));  
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}


}
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"




namespace BEngine
{

	OrthographicCamera::OrthographicCamera() 
	{
		m_ProjectionMatrix = (glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f));
		m_MVMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_MVPMatrix = m_MVMatrix;
	}

	void OrthographicCamera::UpdateModelMatrix()
	{
	}

	void OrthographicCamera::UpdateViewMatrix()
	{
	}

	void OrthographicCamera::UpdateProjectMatrix()
	{
	}


	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_CameraPosition);
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationSpeed), glm::vec3(0, 0, 1));

		m_ViewMatrix = (transform);
		m_MVMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_MVPMatrix = m_MVMatrix;
	}

	void OrthographicCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EVENT_BIND(OrthographicCamera::OnKeyPressedEvent));

	}
	Ref<void> OrthographicCamera::GetCurrentCamera()
	{
		return Ref<void>();
	}
	bool OrthographicCamera::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == BR_KEY_LEFT || event.GetKeyCode() == BR_KEY_A)
		{
			m_CameraPosition.x -= m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_RIGHT || event.GetKeyCode() == BR_KEY_D)
		{
			m_CameraPosition.x += m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_DOWN || event.GetKeyCode() == BR_KEY_S)
		{
			m_CameraPosition.y -= m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_UP || event.GetKeyCode() == BR_KEY_W)
		{
			m_CameraPosition.y += m_moveSpeed;
		}
		return false;
	}
}
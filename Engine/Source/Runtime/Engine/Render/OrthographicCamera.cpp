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

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position);
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = (transform);
		m_MVMatrix = m_ProjectionMatrix * m_ViewMatrix;
		m_MVPMatrix = m_MVMatrix;
	}

	void OrthographicCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EVENT_BIND(OrthographicCamera::OnKeyPressedEvent));

	}
	bool OrthographicCamera::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == BR_KEY_LEFT)
		{
			m_Position.x -= m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_RIGHT)
		{
			m_Position.x += m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_DOWN)
		{
			m_Position.y -= m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_UP)
		{
			m_Position.y += m_moveSpeed;
		}
		return false;
	}
}
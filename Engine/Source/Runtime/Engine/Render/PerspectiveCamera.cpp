#include "PerspectiveCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>



namespace BEngine
{

	PerspectiveCamera::PerspectiveCamera()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	void PerspectiveCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EVENT_BIND(PerspectiveCamera::OnKeyPressedEvent));

	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position);
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), m_RotationVector);

		m_ViewMatrix = (transform);
		m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	bool PerspectiveCamera::OnKeyPressedEvent(KeyPressedEvent& event)
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
			m_Position.z -= m_moveSpeed;
		}
		if (event.GetKeyCode() == BR_KEY_UP)
		{
			m_Position.z += m_moveSpeed;
		}
		return false;
	}

}
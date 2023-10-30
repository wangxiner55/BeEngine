#include "PerspectiveCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>



namespace BEngine
{

	PerspectiveCamera::PerspectiveCamera() : isFistMove(true), bChanged(false)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
		m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
		lastMousePosition = Input::GetMousePos();
	}

	void PerspectiveCamera::SetIsFirstMove(bool isMove)
	{
		isFistMove = isMove;
	}

	void PerspectiveCamera::Tick(Timestep ts)
	{
		Camera::Tick(ts);
		deltaTime = (float)ts;
		UpdataViewMatrix();
		UpdataProjectionMatrix(fov, 800, 600);
		UpdataMVPMatrix();

	}

	void PerspectiveCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(EVENT_BIND(PerspectiveCamera::OnKeyPressedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(EVENT_BIND(PerspectiveCamera::OnMouseMovementEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(EVENT_BIND(PerspectiveCamera::OnMouseScrollEvent));

	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		if (bChanged)
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
			bChanged = false;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position);
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationSpeed), m_RotationVector) * transform;

		m_ViewMatrix = (transform);
		m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	void PerspectiveCamera::UpdataMVPMatrix()
	{
		m_MVPMatrix = m_ProjectionMatrix * m_ViewMatrix * m_ModelMatrix;
	}

	void PerspectiveCamera::UpdataViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0), m_Position);
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-offsetX), { 0,1,0 }) * transform;
		transform = glm::rotate(glm::mat4(1.0f), glm::radians(-offsetY), { 1,0,0 }) * transform;
		m_ViewMatrix = transform;
	}

	void PerspectiveCamera::UpdataProjectionMatrix(float fov, float width, float height)
	{
		if (bChanged)
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);
			bChanged = false;
		}
	}

	bool PerspectiveCamera::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == BR_KEY_LEFT || Input::IsKeyPressed(BR_KEY_A))
		{
			m_Position.x -= m_moveSpeed * deltaTime;
		}
		if (event.GetKeyCode() == BR_KEY_RIGHT || Input::IsKeyPressed(BR_KEY_D))
		{
			m_Position.x += m_moveSpeed * deltaTime;
		}
		if (event.GetKeyCode() == BR_KEY_DOWN || Input::IsKeyPressed(BR_KEY_S))
		{
			m_Position.z -= m_moveSpeed * deltaTime;
		}
		if (event.GetKeyCode() == BR_KEY_UP || Input::IsKeyPressed(BR_KEY_W))
		{
			m_Position.z += m_moveSpeed * deltaTime;
		}
		return false;
	}

	bool PerspectiveCamera::OnMouseMovementEvent(MouseMovedEvent& event)
	{
		if(isFistMove)
		{
			lastMousePosition.first = event.GetX();
			lastMousePosition.second = event.GetY();
			isFistMove = false;
		}
		float doffsetX = event.GetX() - lastMousePosition.first;
		float doffsetY = event.GetY() - lastMousePosition.second;
		offsetX += doffsetX * deltaTime * m_RotationSpeed;
		offsetY += doffsetY * deltaTime * m_RotationSpeed;


		UpdataViewMatrix();

		lastMousePosition.first = event.GetX();
		lastMousePosition.second = event.GetY();




		return false;
	}

	bool PerspectiveCamera::OnMouseScrollEvent(MouseScrolledEvent& event)
	{
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= event.GetYOffset(); bChanged = true;
		if (fov <= 1.0f)
			fov = 1.0f; 
		if (fov >= 45.0f)
			fov = 45.0f; 
		return false;
	}

}
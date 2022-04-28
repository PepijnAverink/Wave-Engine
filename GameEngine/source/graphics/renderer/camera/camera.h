#pragma once

#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>

class Camera
{
public:

	Camera(const glm::vec3& pos, const glm::vec3& lookAt, float speed = 5.0f, float sensitivity = 0.1f)
		: m_Position(pos), m_LookAt(lookAt), m_Speed(speed), m_Sensitivity(sensitivity)
	{
		m_ViewDirection = glm::normalize(m_Position - m_LookAt);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = -glm::normalize(glm::cross(m_ViewDirection, m_Up));
		m_Up = -glm::normalize(glm::cross(m_Right, m_ViewDirection));
		m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
		m_IsDirty = false;
	}

	void UpdateViewMatrix()
	{
		if (m_IsDirty)
		{
			m_ViewDirection = glm::normalize(m_Position - m_LookAt);
			m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
			m_Right = -glm::normalize(glm::cross(m_ViewDirection, m_Up));
			m_Up = -glm::normalize(glm::cross(m_Right, m_ViewDirection));
			m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
			m_IsDirty = false;
		}
		
	}

	void MoveForward() 
	{	
	
		m_ApplyTranslation -= m_ViewDirection;
		m_IsDirty = true;
	}

	void MoveBackward()
	{

		m_ApplyTranslation += m_ViewDirection;
		m_IsDirty = true;

	}

	void MoveLeft()
	{
		m_ApplyTranslation -= m_Right;
		m_IsDirty = true;

	}

	void MoveRight()
	{
		m_ApplyTranslation += m_Right;
		m_IsDirty = true;

	}

	void ApplyTranslation(float delta)
	{
		m_Position += m_ApplyTranslation * delta * m_Speed;
		m_ViewMatrix[3][0] = -glm::dot(m_Right, m_Position);
		m_ViewMatrix[3][1] = -glm::dot(m_Up, m_Position);
		m_ViewMatrix[3][2] = -glm::dot(m_ViewDirection, m_Position);
		m_IsDirty = false;
		//m_LookAt += m_ApplyTranslation * delta * m_Speed;
	}

	bool HasChanged() { return m_IsDirty; }

	glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 getLookAt() { return m_LookAt; }
	glm::vec3 getViewDirection() { return m_ViewDirection; }
	glm::vec3 getUpVector() { return m_Up; }
	glm::vec3 getRightVector() { return m_Right; }

	
	void SetProjectionMatrix(const glm::mat4& projection) { m_ProjectionMatrix = projection; }
	void SetPosition(const glm::vec3& pos) { m_Position = pos; m_IsDirty = true; }
	void SetLookAt(const glm::vec3& lookAt) { m_LookAt = lookAt; m_IsDirty = true; }
	void SetViewDirection(const glm::vec3& viewDirection) { m_ViewDirection = viewDirection; m_IsDirty = true; }
	


	
protected:

	float m_Speed;
	float m_Sensitivity;

	glm::vec3 m_ApplyTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

	bool m_IsDirty;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::vec3 m_Position;
	glm::vec3 m_LookAt;
	glm::vec3 m_ViewDirection;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

};

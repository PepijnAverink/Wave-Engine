#pragma once

#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>

class Camera
{
public:

	Camera(const glm::vec3& pos, const glm::vec3& lookAt, float speed = 5.0f, float sensitivity = 0.1f);
		

	void UpdateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
		
	}

	inline void MoveForward() 
	{	
	
		m_ApplyTranslation -= m_ViewDirection;
		m_IsTranslationDirty = true;
	}

	inline void MoveBackward()
	{

		m_ApplyTranslation += m_ViewDirection;
		m_IsTranslationDirty = true;

	}

	inline void MoveLeft()
	{
		m_ApplyTranslation -= m_Right;
		m_IsTranslationDirty = true;

	}

	inline void MoveRight()
	{
		m_ApplyTranslation += m_Right;
		m_IsTranslationDirty = true;

	}

	inline void Rotate(int _x, int _y)
	{
		m_Yaw += _x;
		m_Pitch += _y;
		m_IsRotationDirty = true;
	}

	void ApplyRotation(float delta);
	void ApplyTranslation(float delta);
	
	inline bool HasChanged() { return m_IsRotationDirty || m_IsTranslationDirty; }
	inline bool HasRotationChanged() { return m_IsRotationDirty; }
	inline bool HasTranslationChanged() { return m_IsTranslationDirty; }
 	inline glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
	glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }
	glm::vec3 GetPosition() { return m_Position; }
	glm::vec3 getLookAt() { return m_LookAt; }
	glm::vec3 getViewDirection() { return m_ViewDirection; }
	glm::vec3 getUpVector() { return m_Up; }
	glm::vec3 getRightVector() { return m_Right; }

	
	// TODO Fix the corresponding camera vectors
	void SetProjectionMatrix(const glm::mat4& projection) { m_ProjectionMatrix = projection; }
	void SetPosition(const glm::vec3& pos) { m_Position = pos; }
	void SetLookAt(const glm::vec3& lookAt) { m_LookAt = lookAt;  }
	void SetViewDirection(const glm::vec3& viewDirection) { m_ViewDirection = viewDirection; }
	


	
protected:

	float m_Speed;
	float m_Sensitivity;
	const static int MAX_PITCH = 89;

	glm::vec3 m_ApplyTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	bool m_IsTranslationDirty, m_IsRotationDirty;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::vec3 m_Position;
	glm::vec3 m_LookAt;
	glm::vec3 m_ViewDirection;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

};

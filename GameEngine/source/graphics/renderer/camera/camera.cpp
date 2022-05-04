#include "core/stdafx.h"

namespace Graphics
{
	Camera::Camera(const glm::vec3& pos, const glm::vec3& lookAt, float speed, float sensitivity, float yaw)
		: m_Position(pos),
		m_LookAt(lookAt),
		m_Speed(speed),
		m_Sensitivity(sensitivity),
		m_Yaw(yaw)
	{
		m_ViewDirection = glm::normalize(m_Position - m_LookAt);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Right = -glm::normalize(glm::cross(m_ViewDirection, m_Up));
		m_Up = -glm::normalize(glm::cross(m_Right, m_ViewDirection));
		m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, m_Up);
		m_IsTranslationDirty = false;
		m_IsRotationDirty = false;
	}


	void Camera::ApplyTranslation(float delta)
	{
		m_Position += m_ApplyTranslation * delta * m_Speed;
		m_LookAt += m_ApplyTranslation * delta * m_Speed;
		m_ViewMatrix[3][0] = -glm::dot(m_Right, m_Position);
		m_ViewMatrix[3][1] = -glm::dot(m_Up, m_Position);
		m_ViewMatrix[3][2] = -glm::dot(m_ViewDirection, m_Position);
		m_ApplyTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
		m_IsTranslationDirty = false;

	}


	void Camera::ApplyRotation(float delta)
	{
		float pitch = m_Sensitivity * m_Pitch;
		float yaw = m_Yaw * m_Sensitivity;
		//Logger::Log(std::to_string(m_Yaw), LOG_TYPE_INFO);
		/*if (m_Pitch > static_cast<float>(MAX_PITCH))
			m_Pitch = static_cast<float>(MAX_PITCH);
		if (m_Pitch < -static_cast<float>(MAX_PITCH))
			m_Pitch = -static_cast<float>(MAX_PITCH);*/

		m_ViewDirection = glm::vec3(
			cos(glm::radians(90 - yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(90 - yaw)) * cos(glm::radians(pitch))
		);
		m_LookAt = m_Position - m_ViewDirection;
		m_Right = -glm::normalize(glm::cross(m_ViewDirection, glm::vec3(0.0f, 1.0f, 0.0)));
		m_Up = -glm::normalize(glm::cross(m_Right, m_ViewDirection));
		UpdateViewMatrix();
		m_IsRotationDirty = false;
	}
}


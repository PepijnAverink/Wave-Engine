
#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>
namespace Graphics {

	class Perspective : public Camera
	{
	public:
		Perspective(const glm::vec3& pos,
			const glm::vec3& lookAt, float fov, float _near, float _far, float aspect,
			float speed = 20.0f, float sensitivity = 0.1f, float yaw = 0.0f) :
			Camera(pos, lookAt, speed, sensitivity, yaw),
			m_FOV(fov),
			m_Aspect(aspect),
			m_Near(_near),
			m_Far(_far),
			m_IsDirty(false)
		{
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
		}

		inline void SetNear(float _near) { m_Near = _near; m_IsDirty = true; }
		inline void SetFar(float _far) { m_Far = _far; m_IsDirty = true; }
		inline void SetAspect(float aspect) { m_Aspect = aspect; m_IsDirty = true; }
		inline void SetFOV(float fov) { m_FOV = fov; m_IsDirty = true; }

		inline bool HasChanged() { return m_IsDirty; }
		inline void UpdateProjectionMatrix() { m_ProjectionMatrix = HasChanged() ? 
			glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far) : m_ProjectionMatrix; }
	private:
		bool m_IsDirty;
		float m_FOV;
		float m_Aspect;
		float m_Near;
		float m_Far;
	};

}
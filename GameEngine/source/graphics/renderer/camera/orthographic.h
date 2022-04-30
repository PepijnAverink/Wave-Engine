#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>
class Orthographic : public Camera
{
public:
	Orthographic(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec2& _boundsX, const glm::vec2& _boundsY, const glm::vec2& _boundsZ,
		float speed = 20.0f, float sensitivity = 0.1f, float yaw = 0.0f) :
		Camera(pos, lookAt, speed, sensitivity, yaw), m_BoundsX(_boundsX), m_BoundsY(_boundsY), m_BoundsZ(_boundsZ), m_IsDirty(false)
	{
		m_ProjectionMatrix = glm::ortho(m_BoundsX.x, m_BoundsX.y, m_BoundsX.x, m_BoundsX.y, m_BoundsX.x, m_BoundsX.y);
	}

	inline void SetBoundsX(const glm::vec2& _boundsX) { m_BoundsX = _boundsX; m_IsDirty = true; }
	inline void SetBoundsY(const glm::vec2& _boundsY) { m_BoundsY = _boundsY; m_IsDirty = true; }
	inline void SetBoundsZ(const glm::vec2& _boundsZ) { m_BoundsZ = _boundsZ; m_IsDirty = true; }

	
	inline bool HasChanged() { return m_IsDirty; }
	inline void UpdateProjectionMatrix() {
		m_ProjectionMatrix = HasChanged() ?
			glm::ortho(m_BoundsX.x, m_BoundsX.y, m_BoundsX.x, m_BoundsX.y, m_BoundsX.x, m_BoundsX.y) : m_ProjectionMatrix;
	}
	
private:
	bool m_IsDirty;
	glm::vec2 m_BoundsX;
	glm::vec2 m_BoundsY;
	glm::vec2 m_BoundsZ;
};
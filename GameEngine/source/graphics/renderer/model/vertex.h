#pragma once
#include "../dependencies/include/glm/glm.hpp"

namespace Graphics
{ 
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec3 TexCoords;
	};
}
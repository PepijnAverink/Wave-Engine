#pragma once

namespace Graphics
{
	// Used to identify what the functionality of a certain shader object is.
	// Passed in at creation of a shader object.
	enum ShaderType
	{
		SHADER_TYPE_NONE   = 0x00,
		SHADER_TYPE_VERTEX = 0x01, // Vertex Shader
		SHADER_TYPE_PIXEL  = 0x02, // Pixel  Shader
	};
}
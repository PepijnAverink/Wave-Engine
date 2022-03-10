#pragma once
#include "./graphics/api/graphics_api.h"
#include "./graphics/api/interface/debug_mode.h"

class Window;
namespace Graphics
{
	class RenderDeviceDescriptor
	{
	public:
		RenderDeviceDescriptor() = default;

		// Host window
		Window* Window = nullptr;

		// Graphics structures
		GraphicsAPI API       = GraphicsAPI::GRAPHICS_API_NONE;
		DebugMode   DebugMode = DebugMode::DEBUG_MODE_NONE;
	};
}
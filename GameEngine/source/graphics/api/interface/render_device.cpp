#include "./graphics/api/interface/render_device.h"
#include "./graphics/api/vulkan/vk_render_device.h"

#include "./core/logger.h"

namespace Graphics
{
	// Static instance
	static RenderDevice* s_RenderDevice = nullptr;

	RenderDevice* RenderDevice::Create(const RenderDeviceDescriptor* _renderDeviceDescriptor)
	{
		// VULKAN-API
		if (_renderDeviceDescriptor->API == GraphicsAPI::GRAPHICS_API_VULKAN)
			s_RenderDevice = new VKRenderDevice(_renderDeviceDescriptor);


		// Return
		if (s_RenderDevice != nullptr)
			return s_RenderDevice;

		// Error checking and logging
		Logger::Log("No abstraction of 'RenderDevice' object found for: " + GraphicsApiToString(_renderDeviceDescriptor->API), LogType::LOG_TYPE_ERROR);
		return nullptr;
	}

	RenderDevice::RenderDevice(const RenderDeviceDescriptor* _renderDeviceDescriptor)
		: m_API(_renderDeviceDescriptor->API)
		, m_DebugMode(_renderDeviceDescriptor->DebugMode)
	{
		// Correct the debug mode
		CorrectDebugMode();
	}

	RenderDevice::~RenderDevice()
	{ }

	void RenderDevice::CorrectDebugMode()
	{
		switch (m_DebugMode)
		{
		case DebugMode::DEBUG_MODE_ALWAYS :
			m_DebugEnabled = true;
			break;
		case DebugMode::DEBUG_MODE_NEVER :
			m_DebugEnabled = false;
			break;
		case DebugMode::DEBUG_MODE_DEBUG_ONLY :
#if defined(_DEBUG)
			m_DebugEnabled = true;
#else
			m_DebugEnabled = false;
#endif
			break;
		}
	}

	RenderDevice* RenderDevice::GetInstance()
	{
		return s_RenderDevice;
	}
}
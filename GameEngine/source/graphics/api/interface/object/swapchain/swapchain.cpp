//#include "./graphics/api/interface/object/swapchain/swapchain.h"
//#include "./core/window/window.h"
#include "core/stdafx.h"
namespace Graphics
{
	Swapchain::Swapchain(const SwapchainDescriptor* _swapchainDescriptor)
		: m_WindowPtr(_swapchainDescriptor->Window)
		, m_Width(_swapchainDescriptor->Width == 0 ? _swapchainDescriptor->Window->GetWidth() : _swapchainDescriptor->Width)
		, m_Height(_swapchainDescriptor->Height == 0 ? _swapchainDescriptor->Window->GetHeight() : _swapchainDescriptor->Height)
	{ }

	Swapchain::~Swapchain()
	{ }
}
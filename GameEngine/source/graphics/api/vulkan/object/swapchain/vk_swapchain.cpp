//#include "./graphics/api/vulkan/object/swapchain/vk_swapchain.h"
//#include "./graphics/api/vulkan/object/command/vk_command_queue.h"
//#include "./core/window/window.h"
//
//#include "./graphics/api/vulkan/resource/texture/vk_texture2D.h"
//#include "./graphics/api/vulkan/resource/view/vk_texture_view.h"
//#include "./graphics/api/vulkan/resource/vk_resource_format.h"
//
//#include "./graphics/api/vulkan/object/sync/vk_fence.h"
//
//#include <vector>
//#include <algorithm>
#include "core/stdafx.h"

namespace Graphics
{
	VKSwapchain::VKSwapchain(VKRenderDevice* _renderDevice, CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor)
		: Swapchain(_swapchainDescriptor)
	{
		CreateSwapchain(_renderDevice, _commandQueue);
	}

	VKSwapchain::~VKSwapchain()
	{
		for (uint32_t i = 0; i < m_BufferCount; i++)
			((VKTexture2D*)m_Textures[i])->FreeImageView();
		vkDestroySwapchainKHR(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_SwapChainObj, nullptr);
	}
	void VKSwapchain::Resize(CommandQueue* _commandQueue, const uint32_t _width, const uint32_t _height)
	{
		// Cleanup
		for (uint32_t i = 0; i < m_BufferCount; i++)
			((VKTexture2D*)m_Textures[i])->FreeImageView();
		vkDestroySwapchainKHR(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_SwapChainObj, nullptr);
		m_Textures.clear();

		m_Width  = _width;
		m_Height = _height;

		// Create new
		VKRenderDevice* device = (VKRenderDevice*)RenderDevice::GetInstance();
		CreateSwapchain(device, _commandQueue);
	}

	uint32_t VKSwapchain::AquireNewImage(CommandQueue* _commandQueue, Fence* _fence)
	{
		VkResult result = vkAcquireNextImageKHR(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_SwapChainObj, UINT64_MAX, VK_NULL_HANDLE, ((VKFence*)_fence)->GetVKFence(), &m_CurrentBufferIndex);
		return m_CurrentBufferIndex;
	}

	void VKSwapchain::Present(CommandQueue* _commandQueue)
	{
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType			   = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 0;
		presentInfo.swapchainCount     = 1;
		presentInfo.pSwapchains        = &m_SwapChainObj;
		presentInfo.pImageIndices      = &m_CurrentBufferIndex;

		vkQueuePresentKHR(((VKCommandQueue*)_commandQueue)->GetVKQueue(), &presentInfo);
	}

	void VKSwapchain::CreateSwapchain(VKRenderDevice* _renderDevice, CommandQueue* _commandQueue)
	{
		// Capabilites
		VkSurfaceCapabilitiesKHR capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_renderDevice->GetPhysicalDevice(), _renderDevice->GetVKSurface(), &capabilities);

		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(_renderDevice->GetPhysicalDevice(), _renderDevice->GetVKSurface(), &formatCount, nullptr);

		if (formatCount != 0) {
			formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(_renderDevice->GetPhysicalDevice(), _renderDevice->GetVKSurface(), &formatCount, formats.data());
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(_renderDevice->GetPhysicalDevice(), _renderDevice->GetVKSurface(), &presentModeCount, nullptr);

		if (presentModeCount != 0) {
			presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(_renderDevice->GetPhysicalDevice(), _renderDevice->GetVKSurface(), &presentModeCount, presentModes.data());
		}

		VkSurfaceFormatKHR format = formats[0];
		for (const auto& availableFormat : formats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				format = availableFormat;
			}
		}

		VkPresentModeKHR mode = VK_PRESENT_MODE_FIFO_KHR;
		for (const auto& availablePresentMode : presentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				mode = availablePresentMode;
			}
		}

		VkExtent2D extend;
		if (capabilities.currentExtent.width != UINT32_MAX) {
			extend = capabilities.currentExtent;
		}
		else {

			VkExtent2D actualExtent = {
				static_cast<uint32_t>(m_Width),
				static_cast<uint32_t>(m_Height)
			};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
			extend = actualExtent;

			m_Width = extend.width;
			m_Height = extend.height;
		}

		uint32_t imageCount = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
			imageCount = capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = _renderDevice->GetVKSurface();

		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = format.format;
		createInfo.imageColorSpace = format.colorSpace;
		createInfo.imageExtent = extend;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

		uint32_t queueFamilyIndices[] = { _renderDevice->GetGraphicsQueueID(), _renderDevice->GetPresentQueueID() };

		if (_commandQueue->CheckSupportFlag(COMMAND_QUEUE_SUPPORT_BIT_PRESENT)) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
		}

		createInfo.preTransform = capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = mode;
		createInfo.clipped = VK_TRUE;

		if (vkCreateSwapchainKHR(_renderDevice->GetDevice(), &createInfo, nullptr, &m_SwapChainObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'Swapchain' object.", LogType::LOG_TYPE_ERROR);

		std::vector<VkImage> images;
		vkGetSwapchainImagesKHR(_renderDevice->GetDevice(), m_SwapChainObj, &imageCount, nullptr);
		images.resize(imageCount);
		vkGetSwapchainImagesKHR(_renderDevice->GetDevice(), m_SwapChainObj, &imageCount, images.data());
		m_BufferCount = imageCount;
		m_Format = ResolveResourceFormat(format.format);

		Texture2DDescriptor textureDesc = {};
		textureDesc.Width = m_Width;
		textureDesc.Height = m_Height;
		textureDesc.Format = ResolveResourceFormat(format.format);

		for (uint32_t i = 0; i < m_BufferCount; i++)
		{
			textureDesc.Name = "SwapchainImage" + i;
			m_Textures.push_back(new VKTexture2D(_renderDevice, images[i], &textureDesc));
		}
	}
}
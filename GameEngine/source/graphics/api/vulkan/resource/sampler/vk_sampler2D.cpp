#include "core/stdafx.h"

namespace Graphics
{
	VKSampler2D::VKSampler2D(VKRenderDevice* _renderDevice, const Sampler2DDescriptor* _sampler2DDescriptor)
		: Sampler2D(_sampler2DDescriptor)
	{
		VkPhysicalDeviceProperties properties{};
		vkGetPhysicalDeviceProperties(_renderDevice->GetPhysicalDevice(), &properties);

		VkSamplerCreateInfo samplerInfo{};
		samplerInfo.sType					= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter				= ResolveVKFilterMode(_sampler2DDescriptor->Filter);
		samplerInfo.minFilter				= ResolveVKFilterMode(_sampler2DDescriptor->Filter);
		samplerInfo.addressModeU			= ResolveVKAddressMode(_sampler2DDescriptor->AddressU);
		samplerInfo.addressModeV			= ResolveVKAddressMode(_sampler2DDescriptor->AddressV);
		samplerInfo.addressModeW			= ResolveVKAddressMode(_sampler2DDescriptor->AddressW);
		samplerInfo.anisotropyEnable		= VK_TRUE;
		samplerInfo.maxAnisotropy			= properties.limits.maxSamplerAnisotropy;
		samplerInfo.borderColor				= VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable			= VK_FALSE;
		samplerInfo.compareOp				= VK_COMPARE_OP_ALWAYS;
		samplerInfo.mipmapMode				= VK_SAMPLER_MIPMAP_MODE_LINEAR;

		if (vkCreateSampler(_renderDevice->GetDevice(), &samplerInfo, nullptr, &m_SamplerObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create shader module.", LogType::LOG_TYPE_ERROR);

	}
	VKSampler2D::~VKSampler2D()
	{
		vkDestroySampler(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_SamplerObj, nullptr);
	}
}
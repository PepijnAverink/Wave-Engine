#pragma once
#include "./graphics/api/interface/object/sync/fence.h"
#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKFence final : public Fence
	{
	public:
		VKFence(VKRenderDevice* _renderDevice, const FenceDescriptor* _fenceDescriptor);
		virtual ~VKFence();

		virtual void Reset() override;
		virtual void WaitForFence() override;

		inline VkFence GetVKFence() const { return m_FenceObj; }

	private:
		VkFence m_FenceObj;
	};
}
#pragma once
//#include "./graphics/api/interface/resource/buffer/buffer.h"
//#include "./graphics/api/vulkan/vk_render_device.h"

namespace Graphics
{
	class VKBuffer final : public Buffer
	{
	public:
		VKBuffer(VKRenderDevice* _renderDevice, const BufferDescriptor* _bufferDescriptor);
		virtual ~VKBuffer();

		virtual void SetData(void* _data, const uint32_t _size) override;

		inline VkBuffer GetVKBuffer() const { return m_BufferObj; }
		inline VkIndexType GetIndexFormat() const { return m_IndexFormat; }

	private:
		uint32_t FindMemoryType(VKRenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

		VkBuffer       m_BufferObj;
		VkDeviceMemory m_BufferMemory;

		VkIndexType m_IndexFormat;
	};
}
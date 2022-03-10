#include "./graphics/api/vulkan/resource/buffer/vk_buffer.h"
#include "./graphics/api/vulkan/resource/buffer/vk_buffer_usage.h"
#include "./graphics/api/vulkan/resource/vk_resource_memory_type.h"
#include "./graphics/api/vulkan/resource/vk_resource_format.h"

namespace Graphics
{
	VKBuffer::VKBuffer(VKRenderDevice* _renderDevice, const BufferDescriptor* _bufferDescriptor)
		: Buffer(_bufferDescriptor)
		, m_IndexFormat(ResolveVKIndexFormat(m_Layout.GetElements()[0].Type))
	{
		VkDeviceSize bufferSize = _bufferDescriptor->Size;

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType	   = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size		   = _bufferDescriptor->Size;
		bufferInfo.usage	   = ResolveVKBufferUsage(_bufferDescriptor->Usage);
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(_renderDevice->GetDevice(), &bufferInfo, nullptr, &m_BufferObj) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'VKBuffer' object.", LogType::LOG_TYPE_ERROR);

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(_renderDevice->GetDevice(), m_BufferObj, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType			  = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize  = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(_renderDevice, memRequirements.memoryTypeBits, ResoleVKResourceMemoryType(_bufferDescriptor->MemoryType));

		if (vkAllocateMemory(_renderDevice->GetDevice(), &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS)
			Logger::Log("VK_ERROR - Failed to create 'VKBuffer' object.", LogType::LOG_TYPE_ERROR);

		vkBindBufferMemory(_renderDevice->GetDevice(), m_BufferObj, m_BufferMemory, 0);

		// Set the data
		if (_bufferDescriptor->Data != nullptr)
			SetData(_bufferDescriptor->Data, m_Size);
	}

	VKBuffer::~VKBuffer()
	{
		vkDestroyBuffer(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_BufferObj, nullptr);
		vkFreeMemory(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_BufferMemory, nullptr);
	}

	void VKBuffer::SetData(void* _data, const uint32_t _size)
	{
		void* data;
		vkMapMemory(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_BufferMemory, 0, m_Size, 0, &data);
		memcpy(data, _data, (size_t)_size);
		vkUnmapMemory(((VKRenderDevice*)RenderDevice::GetInstance())->GetDevice(), m_BufferMemory);
	}

	uint32_t VKBuffer::FindMemoryType(VKRenderDevice* _renderDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(_renderDevice->GetPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		Logger::Log("VK_ERROR - Failed to find suitable memory type.", LogType::LOG_TYPE_ERROR);
		return 0;
	}
}
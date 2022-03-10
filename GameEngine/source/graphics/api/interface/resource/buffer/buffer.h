#pragma once
#include "./graphics/api/interface/resource/buffer/buffer_descriptor.h"

namespace Graphics
{
	class Buffer
	{
	public:
		Buffer(const BufferDescriptor* _bufferDescriptor);
		virtual ~Buffer();

		virtual void SetData(void* _data, const uint32_t _size) = 0;

		inline uint32_t GetSize() const { return m_Size; }
		inline BufferUsage GetUsage() const { return m_Usage; }
		inline const BufferLayout& GetBufferLayout() const { return m_Layout; }

	protected:
		uint32_t m_Size;

		BufferUsage m_Usage;
		BufferLayout m_Layout;
	};
}
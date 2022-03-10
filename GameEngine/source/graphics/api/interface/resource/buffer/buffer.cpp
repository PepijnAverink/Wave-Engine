#include "./graphics/api/interface/resource/buffer/buffer.h"

namespace Graphics
{
	Buffer::Buffer(const BufferDescriptor* _bufferDescriptor)
		: m_Size(_bufferDescriptor->Size)
		, m_Usage(_bufferDescriptor->Usage)
		, m_Layout(_bufferDescriptor->BufferLayout)
	{ }

	Buffer::~Buffer()
	{ }
}
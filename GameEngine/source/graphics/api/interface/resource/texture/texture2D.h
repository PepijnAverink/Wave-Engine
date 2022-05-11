#pragma once
//#include "./graphics/api/interface/resource/texture/texture2D_descriptor.h"
//#include "./graphics/api/interface/resource/resource_format.h"
namespace Graphics
{
	class Texture2D
	{
	public:
		Texture2D(const Texture2DDescriptor* _texture2DDescriptor);
		virtual ~Texture2D();

		// Get dimensions
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		inline ResourceFormat GetFormat() const { return m_Format; }

	protected:
		uint32_t m_Width;
		uint32_t m_Height;

		ResourceFormat m_Format = ResourceFormat::RESOURCE_FORMAT_NONE;
		ResourceState m_State   = ResourceState::RESOURCE_STATE_NONE;
	};
}
#pragma once
//#include "./graphics/api/interface/object/swapchain/swapchain_descriptor.h"
#include "graphics/api/interface/resource/resource_format.h"
#include <vector>

namespace Graphics
{
	class CommandQueue;
	class Fence;

	class Texture2D;
	class TextureView;
	class Swapchain
	{
	public:
		Swapchain(const SwapchainDescriptor* _swapchainDescriptor);
		virtual ~Swapchain();

		virtual void Resize(CommandQueue* _commandQueue, const uint32_t _width, const uint32_t _height) = 0;

		virtual uint32_t AquireNewImage(CommandQueue* _commandQueue, Fence* _fence) = 0;
		virtual void Present(CommandQueue* _commandQueue) = 0;

		inline uint32_t GetBufferCount() const { return m_BufferCount; }

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		inline ResourceFormat GetFormat() const { return m_Format; }

		inline TextureView* GetTextureViewAtIndex(const uint32_t _i) const { return m_TextureViews[_i]; }

	protected:
		Window* m_WindowPtr = nullptr;
		uint32_t m_Width;
		uint32_t m_Height;
	

		ResourceFormat m_Format = ResourceFormat::RESOURCE_FORMAT_NONE;

		uint32_t m_BufferCount = 0;
		uint32_t m_CurrentFrameIndex = 0;

		std::vector<Texture2D*>   m_Textures;
		std::vector<TextureView*> m_TextureViews;
	};
}
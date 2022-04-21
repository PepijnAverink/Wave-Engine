#pragma once
//#include "./graphics/api/interface/resource/view/texture_view_descriptor.h"

namespace Graphics
{
	class Texture2D;
	class TextureViewDescriptor;
	class TextureView
	{
	public:
		TextureView(Texture2D* _texture, const TextureViewDescriptor* _textureViewDescriptor);
		virtual ~TextureView();

	private:
		Texture2D* m_Texture = nullptr;
	};
}
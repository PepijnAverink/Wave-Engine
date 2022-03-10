#include "./graphics/api/interface/resource/view/texture_view.h"
#include "./graphics/api/interface/resource/texture/texture2D.h"

namespace Graphics
{
	TextureView::TextureView(Texture2D* _texture, const TextureViewDescriptor* _textureViewDescriptor)
		: m_Texture(_texture)
	{ }

	TextureView::~TextureView()
	{ }
}
//#include "./graphics/api/interface/resource/texture/texture2D.h"
#include "core/stdafx.h"

namespace Graphics
{
	Texture2D::Texture2D(const Texture2DDescriptor* _texture2DDescriptor)
		: m_Width(_texture2DDescriptor->Width)
		, m_Height(_texture2DDescriptor->Height)
		, m_Format(_texture2DDescriptor->Format)
		, m_State(_texture2DDescriptor->State)
	{ }

	Texture2D::~Texture2D()
	{ }
}
//#include "./graphics/renderer/renderer3D.h"
#include "core/stdafx.h"
namespace Graphics
{
	void Renderer3D::OnInitialize(RendererBackend* _backend)
	{
		m_RendererBackend = _backend;
	}

	void Renderer3D::OnTerminate()
	{

	}
}
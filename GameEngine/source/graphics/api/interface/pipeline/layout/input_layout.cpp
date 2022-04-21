//#include "./graphics/api/interface/pipeline/layout/input_layout.h"
#include "core/stdafx.h"

namespace Graphics
{
	InputLayout::InputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor)
		: m_Layouts(_inputLayoutDescriptor->Layouts)
	{ }

	InputLayout::~InputLayout()
	{

	}
}
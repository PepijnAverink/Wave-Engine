#include "./graphics/api/interface/pipeline/layout/input_layout.h"

namespace Graphics
{
	InputLayout::InputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor)
		: m_Layouts(_inputLayoutDescriptor->Layouts)
	{ }

	InputLayout::~InputLayout()
	{

	}
}
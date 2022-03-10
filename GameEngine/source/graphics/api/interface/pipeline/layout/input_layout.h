#pragma once
#include "./graphics/api/interface/pipeline/layout/input_layout_descriptor.h"

#include <vector>

namespace Graphics
{
	class InputLayout
	{
	public:
		InputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor);
		virtual ~InputLayout();

		const std::vector<InputSet>& GetLayouts() const { return m_Layouts; }

		std::vector<InputSet>::iterator begin() { return m_Layouts.begin(); }
		std::vector<InputSet>::iterator end() { return m_Layouts.end(); }
		std::vector<InputSet>::const_iterator begin() const { return m_Layouts.begin(); }
		std::vector<InputSet>::const_iterator end()	  const { return m_Layouts.end(); }

	protected:
		std::vector<InputSet> m_Layouts;
	};
}
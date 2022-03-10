#pragma once
#include "./graphics/api/interface/pipeline/layout/vertex_element.h"

#include <vector>

namespace Graphics
{
	class VertexLayout
	{
	public:
		VertexLayout() = default;
		VertexLayout(std::initializer_list<VertexElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		const std::vector<VertexElement>& GetElements() const { return m_Elements; }

		std::vector<VertexElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexElement>::const_iterator end()	 const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<VertexElement>  m_Elements;
		uint32_t					m_Stride = 0;
	};
}
#pragma once
#include "./graphics/api/interface/resource/resource_format.h"

#include <string>

namespace Graphics
{
	class VertexElement
	{
	public:
		VertexElement() = default;
		VertexElement(const std::string& _name, ResourceFormat _type, bool _normalized = false)
			: Name(_name)
			, Type(_type)
			, Size(GetFormatSize(_type))
			, Offset(0)
			, Normalized(_normalized)
		{ }

		std::string		Name;
		ResourceFormat	Type;
		uint32_t		Size;
		size_t			Offset;
		bool			Normalized;
	};
}
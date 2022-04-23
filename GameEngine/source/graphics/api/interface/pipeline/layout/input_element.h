#pragma once
//#include "./graphics/api/interface/pipeline/layout/input_type.h"
#include "./graphics/api/interface/resource/shader/shader_type_flags.h"

#include <string>

namespace Graphics
{
	class InputElement
	{
	public:
		InputElement() = default;
		InputElement(const std::string& _name, InputType _type, ShaderTypeFlag _stageFlag, uint32_t _registerId, uint32_t _count = 1)
			: Name(_name)
			, Type(_type)
			, StageFlag(_stageFlag)
			, BaseRegisterID(_registerId)
			, Count(_count)
		{}

		std::string     Name;
		InputType       Type;
		ShaderTypeFlag  StageFlag;
		uint32_t	    BaseRegisterID;
		// Count is used for regular elements
		// Size is used for constants
		union { uint32_t Count; uint32_t Size; };
	};
}
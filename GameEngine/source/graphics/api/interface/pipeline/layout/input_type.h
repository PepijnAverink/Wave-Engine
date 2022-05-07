#pragma once

namespace Graphics
{
	enum InputType
	{
		INPUT_TYPE_NONE			  = 0x00,
		INPUT_TYPE_ERROR		  = 0x01,
		INPUT_TYPE_CONSTANT       = 0x02,
		INPUT_TYPE_UNIFORM_BUFFER = 0x03,
		INPUT_TYPE_SAMPLER2D	  = 0x04,
	};
}
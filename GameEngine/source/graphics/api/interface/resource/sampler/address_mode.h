#pragma once

namespace Graphics
{
	enum AddressMode
	{
		ADDRESS_MODE_NONE			 = 0x00,
		ADDRESS_MODE_ERROR			 = 0x01,
		ADDRESS_MODE_REPEAT			 = 0x02,
		ADDRESS_MODE_MIRROR			 = 0x03,
		ADDRESS_MODE_CLAMP_TO_EDGE	 = 0x04,
		ADDRESS_MODE_CLAMP_TO_BORDER = 0x05,
	};
}
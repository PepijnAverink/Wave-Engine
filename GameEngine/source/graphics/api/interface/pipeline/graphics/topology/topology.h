#pragma once

namespace Graphics
{
	enum Topology
	{
		TOPOLOGY_NONE           = 0x00,
		TOPOLOGY_ERROR		    = 0x01,
		TOPOLOGY_POINT_LIST     = 0x02,
		TOPOLOGY_LINE_STRIP     = 0x03,
		TOPOLOGY_LINE_LIST      = 0x04,
		TOPOLOGY_TRIANGLE_STRIP = 0x05,
		TOPOLOGY_TRIANGLE_LIST  = 0x06,
	};
}
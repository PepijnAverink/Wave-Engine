#pragma once
#include "./graphics/api/interface/pipeline/graphics/topology/topology.h"
#include "./core/logger.h"

#include <vulkan/vulkan.h>

namespace Graphics
{
	inline VkPrimitiveTopology ResolveVKTopology(Topology _topology)
	{
		switch (_topology)
		{
			case Topology::TOPOLOGY_POINT_LIST :
				return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			case Topology::TOPOLOGY_LINE_STRIP:
				return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
			case Topology::TOPOLOGY_LINE_LIST :
				return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			case Topology::TOPOLOGY_TRIANGLE_STRIP:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
			case Topology::TOPOLOGY_TRIANGLE_LIST:
				return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		}

		Logger::Log("VK_ERROR - Failed to resolve Topology: " + _topology, LogType::LOG_TYPE_ERROR);
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	}
}
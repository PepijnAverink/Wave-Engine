#pragma once

#include <fstream>
#include <streambuf>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <optional>
#include <set>

#include "core/logger.h"
#include "core/performance/timer.h"
#include "core/event/event.h"
#include "core/event/event_category.h"
#include "core/event/event_dispatcher.h"
#include "core/event/event_type.h"
#include "core/event/window/window_resize_event.h"
#include "core/event/input/key_down_event.h"
#include "core/event/input/key_up_event.h"
#include "core/event/input/mouse_left_down_event.h"
#include "core/event/input/mouse_left_up_event.h"
#include "core/event/input/mouse_move_event.h"
#include "core/event/input/mouse_right_down_event.h"
#include "core/event/input/mouse_right_up_event.h"
#include "core/window/window.h"


#include "core/system/file_system.h"
#if defined(_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>



#include "graphics/api/graphics_api.h"
#include "graphics/api/interface/debug_mode.h"
#include "graphics/api/interface/render_device.h"
#include "graphics/api/interface/render_device_descriptor.h"



#include "graphics/api/interface/object/command/command_queue_type.h"
#include "graphics/api/interface/object/command/command_pool_descriptor.h"
#include "graphics/api/interface/object/command/command_pool.h"
#include "graphics/api/interface/object/command/command_buffer_type.h"
#include "graphics/api/interface/object/command/command_buffer_descriptor.h"
#include "graphics/api/interface/object/command/command_buffer.h"
#include "graphics/api/interface/object/command/command_queue_support_bit.h"
#include "graphics/api/interface/object/command/command_queue_descriptor.h"
#include "graphics/api/interface/object/command/command_queue.h"



#include "graphics/api/interface/resource/resource_format.h"


#include "graphics/api/interface/object/swapchain/swapchain_descriptor.h"
#include "graphics/api/interface/object/swapchain/swapchain.h"

#include "graphics/api/interface/object/sync/fence_descriptor.h"
#include "graphics/api/interface/object/sync/fence.h"


#include "graphics/api/interface/pipeline/framebuffer/frame_buffer.h"
#include "graphics/api/interface/pipeline/framebuffer/frame_buffer_attachment.h"
#include "graphics/api/interface/pipeline/framebuffer/frame_buffer_attachment_type.h"
#include "graphics/api/interface/pipeline/framebuffer/frame_buffer_descriptor.h"

#include "graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
#include "graphics/api/interface/pipeline/graphics/graphics_pipeline_descriptor.h"
#include "graphics/api/interface/pipeline/graphics/rasterizer/cull_mode.h"
#include "graphics/api/interface/pipeline/graphics/rasterizer/fill_mode.h"
#include "graphics/api/interface/pipeline/graphics/rasterizer/winding_order.h"
#include "graphics/api/interface/pipeline/graphics/topology/topology.h"
#include "graphics/api/interface/pipeline/graphics/viewport/scissor_rect.h"
#include "graphics/api/interface/pipeline/graphics/viewport/view_port.h"

#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_pool.h"
#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_pool_descriptor.h"
#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_pool_size.h"
#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_set.h"
#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_set_descriptor.h"

#
#include "graphics/api/interface/pipeline/layout/input_set.h"
#include "graphics/api/interface/resource/shader/shader_type_flags.h"
#include "graphics/api/interface/pipeline/layout/input_type.h"
#include "graphics/api/interface/pipeline/layout/input_layout_descriptor.h"
#include "graphics/api/interface/pipeline/layout/input_element.h"
#include "graphics/api/interface/pipeline/layout/input_layout.h"

#include "graphics/api/interface/pipeline/layout/vertex_element.h"
#include "graphics/api/interface/pipeline/layout/vertex_layout.h"

#include "graphics/api/interface/pipeline/renderpass/render_pass.h"
#include "graphics/api/interface/pipeline/renderpass/render_pass_attachment.h"
#include "graphics/api/interface/pipeline/renderpass/render_pass_attachment_type.h"
#include "graphics/api/interface/pipeline/renderpass/render_pass_descriptor.h"
#include "graphics/api/interface/pipeline/renderpass/render_pass_load_op.h"
#include "graphics/api/interface/pipeline/renderpass/render_pass_store_op.h"


#include "graphics/api/interface/resource/buffer/buffer_usage.h"
#include "graphics/api/interface/resource/resource_bind_flags.h"
#include "graphics/api/interface/resource/resource_memory_type.h"
#include "graphics/api/interface/resource/buffer/buffer_descriptor.h"
#include "graphics/api/interface/resource/buffer/buffer.h"





#include "graphics/api/interface/resource/resource_state.h"
#include "graphics/api/interface/resource/resource_type.h"

#include "graphics/api/interface/resource/shader/shader_type.h"

#include "graphics/api/interface/resource/shader/shader_descriptor.h"
#include "graphics/api/interface/resource/shader/shader.h"



#include "graphics/api/interface/resource/texture/texture2D_descriptor.h"
#include "graphics/api/interface/resource/texture/texture2D.h"


#include "graphics/api/interface/resource/view/resource_view_type.h"
#include "graphics/api/interface/resource/view/texture_view_descriptor.h"
#include "graphics/api/interface/resource/view/texture_view.h"



#include "graphics/api/interface/render_device_descriptor.h"
#include "graphics/api/interface/render_device.h"

#include "graphics/api/vulkan/vk_render_device.h"
#include "graphics/api/vulkan/resource/buffer/vk_buffer_usage.h"
#include "graphics/api/vulkan/resource/buffer/vk_buffer.h"
#include "graphics/api/vulkan/resource/texture/vk_texture2D.h"

#include "graphics/api/vulkan/object/command/vk_command_buffer.h"
#include "graphics/api/vulkan/object/command/vk_command_pool.h"
#include "graphics/api/vulkan/object/command/vk_command_queue.h"

#include "graphics/api/vulkan/resource/vk_resource_format.h"
#include "graphics/api/vulkan/resource/vk_resource_state.h"
#include "graphics/api/vulkan/resource/vk_resource_memory_type.h"
#include "graphics/api/vulkan/resource/view/vk_texture_view.h"
#include "graphics/api/vulkan/object/swapchain/vk_swapchain.h"

#include "graphics/api/vulkan/object/sync/vk_fence.h"

#include "graphics/api/vulkan/pipeline/framebuffer/vk_frame_buffer.h"

#include "graphics/api/vulkan/pipeline/graphics/rasterizer/vk_cull_mode.h"
#include "graphics/api/vulkan/pipeline/graphics/rasterizer/vk_fill_mode.h"
#include "graphics/api/vulkan/pipeline/graphics/rasterizer/vk_winding_order.h"

#include "graphics/api/vulkan/pipeline/graphics/topology/vk_topology.h"
#include "graphics/api/vulkan/resource/shader/vk_shader_type_flags.h"
#include "graphics/api/vulkan/resource/shader/vk_shader.h"
#include "graphics/api/vulkan/pipeline/graphics/vk_graphics_pipeline.h"


#include "graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_set.h"
#include "graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_pool.h"

#include "graphics/api/vulkan/pipeline/layout/vk_input_layout.h"
#include "graphics/api/vulkan/pipeline/layout/vk_input_type.h"

#include "graphics/api/vulkan/pipeline/renderpass/vk_render_pass.h"
#include "graphics/api/vulkan/pipeline/renderpass/vk_render_pass_load_op.h"
#include "graphics/api/vulkan/pipeline/renderpass/vk_render_pass_store_op.h"

#include "graphics/renderer/camera/camera.h"
#include "graphics/renderer/camera/perspective.h"
#include "graphics/renderer/camera/orthographic.h"

#include "graphics/renderer/material/material.h"
#include "graphics/renderer/material/material_instance.h"

#include "graphics/renderer/model/default/quad.h"
#include "graphics/renderer/model/mesh.h"
#include "graphics/renderer/model/sub_mesh.h"
#include "graphics/renderer/model/vertex.h"

#include "graphics/renderer/renderer3D.h"
#include "graphics/renderer/renderer_backend.h"

#include "utility/hash_utility.h"
#include "utility/string_utility.h"
#include "utility/version.h"








#pragma once

#include "core/window/window.h"

#include "graphics/api/interface/render_device.h"
#include "graphics/api/interface/object/command/command_queue.h"
#include "graphics/api/interface/object/swapchain/swapchain.h"
#include "graphics/api/interface/object/command/command_pool.h"
#include "graphics/api/interface/object/command/command_buffer.h"
#include "graphics/api/interface/object/sync/fence.h"

#include "graphics/api/interface/pipeline/renderpass/render_pass.h"
#include "graphics/api/interface/pipeline/framebuffer/frame_buffer.h"
#include "graphics/api/interface/pipeline/graphics/graphics_pipeline.h"
#include "graphics/api/interface/pipeline/layout/input_layout.h"

#include "graphics/api/interface/resource/shader/shader.h"
#include "graphics/api/interface/resource/buffer/buffer.h"

#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_pool.h"
#include "graphics/api/interface/pipeline/layout/descriptor/descriptor_set.h"

#include "core/event/window/window_resize_event.h"

#include "../../Sandbox/source/application.h"
#include "./core/event/event_dispatcher.h"

#include <../../GameEngine/dependencies/include/glm/glm.hpp>
#include <../../GameEngine/dependencies/include/glm/gtc/matrix_transform.hpp>

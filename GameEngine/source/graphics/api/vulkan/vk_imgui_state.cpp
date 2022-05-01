#include "core/stdafx.h"
#include "imgui.h"
#include "imgui_impl_vulkan.h"
#include "imgui_impl_win32.h"

namespace Graphics {
	VKImguiState::VKImguiState(VKRenderDevice* vk_render_device, Window* _window, VKCommandQueue* _graphicsQueue, VKRenderPass* _renderPass, VKCommandBuffer* _commandBuffer) {
		//1: create descriptor pool for IMGUI
	// the size of the pool is very oversize, but it's copied from imgui demo itself.
		VkDescriptorPoolSize pool_sizes[] =
		{
			{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
			{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
			{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
			{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
		};

		VkDescriptorPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		pool_info.maxSets = 1000;
		pool_info.poolSizeCount = std::size(pool_sizes);
		pool_info.pPoolSizes = pool_sizes;

		m_imguiPool = new VkDescriptorPool();
		vkCreateDescriptorPool(vk_render_device->GetDevice(), &pool_info, nullptr, m_imguiPool); //TODO add check if descriptorpool was created successfully


		// 2: initialize imgui library

		//this initializes the core structures of imgui
		ImGui::CreateContext();

		//this initializes imgui for SDL
		ImGui_ImplWin32_Init(_window);


		//this initializes imgui for Vulkan
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = vk_render_device->GetVKInstance();
		init_info.PhysicalDevice = vk_render_device->GetPhysicalDevice();
		init_info.Device = vk_render_device->GetDevice();
		init_info.Queue = _graphicsQueue->GetVKQueue();
		init_info.DescriptorPool = *m_imguiPool;
		init_info.MinImageCount = 3;
		init_info.ImageCount = 3;
		init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

		ImGui_ImplVulkan_Init(&init_info, _renderPass->GetVKRenderPass());

		//execute a gpu command to upload imgui font textures
		ImGui_ImplVulkan_CreateFontsTexture(_commandBuffer->GetVKCommandBuffer());
		
		//clear font textures from cpu data
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}
	void VKImguiState::DestroyBackend(VKRenderDevice* vk_render_device) {
		vkDestroyDescriptorPool(vk_render_device->GetDevice(), *m_imguiPool, nullptr);
		ImGui_ImplVulkan_Shutdown();
	}

	void VKImguiState::InitFrame() {
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();


		//imgui commands
		ImGui::ShowDemoWindow();

		ImGui::Render();

		m_draw_data = ImGui::GetDrawData();
		
	}
	void VKImguiState::RenderFrame(VKFrameBuffer* vk_frame, VKCommandBuffer* vk_command_buffer, VKRenderPass* vk_render_pass, uint32_t width, uint32_t height, VkClearValue* clear_value) {
		{
			VkRenderPassBeginInfo info = {};
			info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			info.renderPass = vk_render_pass->GetVKRenderPass();
			info.framebuffer = vk_frame->GetVKFrameBuffer();
			info.renderArea.extent.width = width;
			info.renderArea.extent.height = height;
			info.clearValueCount = 1;
			info.pClearValues = clear_value;
			vkCmdBeginRenderPass(vk_command_buffer->GetVKCommandBuffer(), &info, VK_SUBPASS_CONTENTS_INLINE);
		}

		// Record dear imgui primitives into command buffer
		ImGui_ImplVulkan_RenderDrawData(m_draw_data, vk_command_buffer->GetVKCommandBuffer());

		// Submit command buffer
		vkCmdEndRenderPass(vk_command_buffer->GetVKCommandBuffer());
		
	}
}

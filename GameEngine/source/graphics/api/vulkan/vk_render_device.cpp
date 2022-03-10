#include "./graphics/api/vulkan/vk_render_device.h"

#include "./graphics/api/vulkan/object/command/vk_command_pool.h"
#include "./graphics/api/vulkan/object/command/vk_command_buffer.h"
#include "./graphics/api/vulkan/object/command/vk_command_queue.h"
#include "./graphics/api/vulkan/object/swapchain/vk_swapchain.h"
#include "./graphics/api/vulkan/object/sync/vk_fence.h"

#include "./graphics/api/vulkan/pipeline/graphics/vk_graphics_pipeline.h"
#include "./graphics/api/vulkan/pipeline/layout/vk_input_layout.h"
#include "./graphics/api/vulkan/pipeline/renderpass/vk_render_pass.h"
#include "./graphics/api/vulkan/pipeline/framebuffer/vk_frame_buffer.h"

#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_pool.h"
#include "./graphics/api/vulkan/pipeline/layout/descriptor/vk_descriptor_set.h"

#include "./graphics/api/vulkan/resource/buffer/vk_buffer.h"
#include "./graphics/api/vulkan/resource/shader/vk_shader.h"

#include "./core/window/window.h"
#include "./core/logger.h"

#include <iostream>
#include <optional>
#include <vector>
#include <set>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
        func(instance, debugMessenger, pAllocator);
}

// Debug callback
// Validation layer message print
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

namespace Graphics
{
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR _surface);

	VKRenderDevice::VKRenderDevice(const RenderDeviceDescriptor* _renderDeviceDescriptor)
        : RenderDevice(_renderDeviceDescriptor)
	{
		// Corrct debug mode
        if (m_DebugEnabled == true)
            m_DebugEnabled = CheckValidationLayerSupport();

        // Current extensions
        std::vector<const char*> extensions = { "VK_KHR_surface" };
        {
#if defined(_WIN32)
            extensions.push_back("VK_KHR_win32_surface");
#endif
            if (m_DebugEnabled)
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        // Application information
        VkApplicationInfo appInfo{};
        appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName   = _renderDeviceDescriptor->Window->GetTitle().c_str();
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName        = "No Engine";
        appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion         = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo        = &appInfo;
        createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount       = 0;
        createInfo.pNext                   = nullptr;

        // Enable debug layer
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
        if (m_DebugEnabled == true) {
            debugCreateInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            debugCreateInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            debugCreateInfo.pfnUserCallback = debugCallback;

            createInfo.enabledLayerCount   = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }

        // Create and error check vulkan instance
        if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
            Logger::Log("VK_ERROR - Failed to create the vulkan instance.", LogType::LOG_TYPE_ERROR);

        // Enable debug messenger if debugmode is enabled
        if (m_DebugEnabled == true)
            if (CreateDebugUtilsMessengerEXT(m_Instance, &debugCreateInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
                Logger::Log("VK_ERROR - Failed to serup the vulkan debug messenger.", LogType::LOG_TYPE_ERROR);

        // Surface which is associated with the window
        VkWin32SurfaceCreateInfoKHR surfaceCreateInfo;
        surfaceCreateInfo.sType     = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surfaceCreateInfo.pNext     = NULL;
        surfaceCreateInfo.flags     = 0;
        surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
        surfaceCreateInfo.hwnd      = _renderDeviceDescriptor->Window->GetWindowHandle();

        // Craete and error check the surface
        if (vkCreateWin32SurfaceKHR(m_Instance, &surfaceCreateInfo, NULL, &m_Surface) != VK_SUCCESS)
            Logger::Log("VK_ERROR - Failed to create surface.", LogType::LOG_TYPE_ERROR);

        // Get the hardware device
        GetVKPhysicalDevice();


        {
            QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice, m_Surface);

            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

            float queuePriority = 1.0f;
            for (uint32_t queueFamily : uniqueQueueFamilies) {
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = queueFamily;
                queueCreateInfo.queueCount = 1;
                queueCreateInfo.pQueuePriorities = &queuePriority;
                queueCreateInfos.push_back(queueCreateInfo);
            }

            VkPhysicalDeviceFeatures deviceFeatures{};

            VkDeviceCreateInfo createInfo{};
            createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            createInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
            createInfo.pQueueCreateInfos       = queueCreateInfos.data();
            createInfo.pEnabledFeatures        = &deviceFeatures;
            createInfo.enabledExtensionCount   = static_cast<uint32_t>(deviceExtensions.size());
            createInfo.ppEnabledExtensionNames = deviceExtensions.data();
            createInfo.enabledLayerCount = 0;

            if (m_DebugEnabled == true) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            }

            if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS) {
                throw std::runtime_error("failed to create logical device!");
            }

            m_GraphicsQueueID = indices.graphicsFamily.value();
            m_PresentQueueID = indices.presentFamily.value();
        }
	}

	VKRenderDevice::~VKRenderDevice()
	{
        vkDestroyDevice(m_Device, nullptr);

        if (m_DebugEnabled == true) 
            DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);

        vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
        vkDestroyInstance(m_Instance, nullptr);
	}

    uint32_t VKRenderDevice::GetQueueFamilyID(const CommandQueueType _type) const
    {
        // TODO:: add support for other types of queues
        if (_type == CommandQueueType::COMMAND_QUEUE_TYPE_GRAPHICS)
            return m_GraphicsQueueID;

        return 0;
    }

    CommandPool* VKRenderDevice::CreateCommandPool(const CommandPoolDescriptor* _commandPoolDescriptor)
    {
        VKCommandPool* commandPool = new VKCommandPool(this, _commandPoolDescriptor);
        return commandPool;
    }

    CommandBuffer* VKRenderDevice::CreateCommandBuffer(const CommandBufferDescriptor* _commandBufferDescriptor)
    {
        VKCommandBuffer* commandBuffer = new VKCommandBuffer(this, _commandBufferDescriptor);
        return commandBuffer;
    }

    CommandQueue* VKRenderDevice::CreateCommandQueue(const CommandQueueDescriptor* _commandQueueDescriptor)
    {
        VKCommandQueue* commandQueue = new VKCommandQueue(this, _commandQueueDescriptor);
        return commandQueue;
    }

    Swapchain* VKRenderDevice::CreateSwapchain(CommandQueue* _commandQueue, const SwapchainDescriptor* _swapchainDescriptor)
    {
        VKSwapchain* swapchain = new VKSwapchain(this, _commandQueue, _swapchainDescriptor);
        return swapchain;
    }

    GraphicsPipeline* VKRenderDevice::CreateGraphicsPipeline(const GraphicsPipelineDescriptor* _graphicsPipelineDescriptor)
    {
        VKGraphicsPipeline* graphicsPipeline = new VKGraphicsPipeline(this, _graphicsPipelineDescriptor);
        return graphicsPipeline;
    }

    InputLayout* VKRenderDevice::CreateInputLayout(const InputLayoutDescriptor* _inputLayoutDescriptor)
    {
        VKInputLayout* inputLayout = new VKInputLayout(this, _inputLayoutDescriptor);
        return inputLayout;
    }

    RenderPass* VKRenderDevice::CreateRenderPass(const RenderPassDescriptor* _renderPassDescriptor)
    {
        RenderPass* renderPass = new VKRenderPass(this, _renderPassDescriptor);
        return renderPass;
    }

    FrameBuffer* VKRenderDevice::CreateFrameBuffer(const FrameBufferDescriptor* _frameBufferDescriptor)
    {
        VKFrameBuffer* frameBuffer = new VKFrameBuffer(this, _frameBufferDescriptor);
        return frameBuffer;
    }

    DescriptorPool* VKRenderDevice::CreateDescriptorPool(const DescriptorPoolDescriptor* _descriptorPoolDescriptor)
    {
        VKDescriptorPool* descroptorPool = new VKDescriptorPool(this, _descriptorPoolDescriptor);
        return descroptorPool;
    }

    Buffer* VKRenderDevice::CreateBuffer(const BufferDescriptor* _bufferDescriptor)
    {
        VKBuffer* buffer = new VKBuffer(this, _bufferDescriptor);
        return buffer;
    }

    Shader* VKRenderDevice::CreateShader(const ShaderDescriptor* _shaderDescriptor)
    {
        VKShader* shader = new VKShader(this, _shaderDescriptor);
        return shader;
    }

    Fence* VKRenderDevice::CreateFence(const FenceDescriptor* _fenceDescriptor)
    {
        VKFence* fence = new VKFence(this, _fenceDescriptor);
        return fence;
    }

    bool VKRenderDevice::CheckValidationLayerSupport()
	{
        // Enumerate over all the layers
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        // Allocate vector for all layers
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        // Loop over all requiered validation layers
        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            // Check if the layer is present
            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            // Layer wasn't found
            if (!layerFound) {
                Logger::Log("VK_ERROR - User tried to turn on validation layer, but this wasn't supported on host device.", LogType::LOG_TYPE_ERROR);
                return false;
            }
        }

        return true;
	}

    void VKRenderDevice::GetVKPhysicalDevice()
    {
        // Get the number of devices
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

        // Error check for deviice not existing
        if (deviceCount == 0) {
            Logger::Log("VK_ERROR - (device_count == 0)", LogType::LOG_TYPE_ERROR);
            return;
        }

        // allocate vector of devices
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

        // Loop over all avaiable devices
        for (const auto& device : devices) {

            {
                // Get total extension count
                uint32_t extensionCount;
                vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

                // Allocate vector of extensions
                std::vector<VkExtensionProperties> availableExtensions(extensionCount);
                vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

                std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
                for (const auto& extension : availableExtensions) {
                    requiredExtensions.erase(extension.extensionName);
                }

                // Not all requirements are meet
                if (requiredExtensions.empty() == false)
                    continue;
            }

            {
                // Get capabilities
                VkSurfaceCapabilitiesKHR capabilities;
                vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_Surface, &capabilities);

                // Get formatCount
                uint32_t formatCount;
                vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, nullptr);

                std::vector<VkSurfaceFormatKHR> formats;
                if (formatCount != 0) {
                    formats.resize(formatCount);
                    vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_Surface, &formatCount, formats.data());
                }

                uint32_t presentModeCount;
                vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, nullptr);

                std::vector<VkPresentModeKHR> presentModes;
                if (presentModeCount != 0) {
                    presentModes.resize(presentModeCount);
                    vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_Surface, &presentModeCount, presentModes.data());
                }

                // Not all requirements are meet
                if (formats.empty() || presentModes.empty())
                    continue;
            }

            {
                QueueFamilyIndices indices = FindQueueFamilies(device, m_Surface);
                if (indices.isComplete() == false)
                    continue;
            }

            // Set device
            m_PhysicalDevice = device;
            return;
        }

        if (m_PhysicalDevice == VK_NULL_HANDLE)
            Logger::Log("VK_ERROR - No physical device found.", LogType::LOG_TYPE_ERROR);
    }

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR _surface) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, _surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }
        //i = 0;
        //for (const auto& queueFamily : queueFamilies) {
        //    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT && queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        //        printf("General purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
        //    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        //        printf("Graphics purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
        //    if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        //        printf("Compute purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
        //    if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        //        printf("Transfer purpose QUEUE: %i, %i\n", queueFamily.queueCount, i);
        //
        //    i++;
        //}
        return indices;
    }
}
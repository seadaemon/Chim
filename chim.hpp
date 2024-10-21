/**
 * @file chim.hpp
 * @author George Power
 * @brief Initializes the SDL window and the Vulkan renderer.
 */
#ifndef CHIM_HPP
#define CHIM_HPP

#define SDL_MAIN_HANDLED
#include "path_config.h"
#include <SDL.h>
#include <SDL_vulkan.h>
#include <algorithm>
#include <cstdint>
#include <exception>
#include <fstream>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <vector>
#include <vulkan/vulkan.hpp>
// #include <SDL_image.h> //TODO: Fix this import

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif
#define LOG(...) std::cout << __VA_ARGS__ << std::endl

namespace chim
{
/**
 * @class ChimException
 * @brief Exception type for anything in the chim namespace.
 */
class ChimException : public std::exception
{
  private:
    std::string message_;

  public:
    ChimException(std::string message) : message_("[CHIM Exception] " + message){};
    virtual const char *what() const throw() { return message_.c_str(); };
    virtual ~ChimException() throw(){};
};

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

/**
 * @class Chim
 * @brief Renders the main window.
 */
class Chim
{

  public:
    Chim();
    ~Chim();

    void Init(void);
    void Run(void);
    void Cleanup(void);

  private:
    void CreateInstance(void); // Create Vulkan instance
    void SetupDebugMessenger(void);
    void CreateSurface(void);
    void PickPhysicalDevice(void);
    void CreateLogicalDevice(void);

    void CreateSwapChain(void);
    void CleanupSwapChain(void);
    void RecreateSwapChain(void);

    void CreateImageViews(void);
    void CreateRenderPass(void);
    void CreateGraphicsPipeline(void);
    void CreateFrameBuffers(void);
    void CreateCommandPool(void);
    void CreateCommandBuffers(void);
    void CreateSyncObjects(void);

    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void DrawFrame(void);

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& create_info);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);
    bool CheckValidationLayerSupport(void);
    std::vector<const char *> GetRequiredExtensions(void);
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                        void *pUserData);
    int RateDeviceSuitability(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    // Swap chain
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    VkShaderModule CreateShaderModule(const std::vector<char>& code);

    static std::vector<char> ReadFile(const std::string& filename);

  private:
    const uint32_t window_width_ = 1280;
    const uint32_t window_height_ = 720;
    bool keep_window_open_ = true;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    uint32_t current_frame_ = 0;
    // SDL
    SDL_Window *window_ = nullptr;
    SDL_Event ev_;
    bool resize_requested_ = false;
    // SDL_Surface* window_icon_ = nullptr; // TBA

    // Vulkan
    VkInstance instance_;
    VkDebugUtilsMessengerEXT debug_messenger_;
    VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
    VkDevice device_;
    VkQueue graphics_queue_;
    VkSurfaceKHR surface_;
    VkQueue present_queue_;
    // Swap chain
    VkSwapchainKHR swap_chain_;
    std::vector<VkImage> swap_chain_images_;
    VkFormat swap_chain_image_format_;
    VkExtent2D swap_chain_extent_;
    std::vector<VkImageView> swap_chain_image_views_;
    std::vector<VkFramebuffer> swap_chain_frame_buffers_;

    VkRenderPass render_pass_;
    VkPipeline graphics_pipeline_;
    VkPipelineLayout pipeline_layout_;

    VkCommandPool command_pool_;

    std::vector<VkCommandBuffer> command_buffers_;
    std::vector<VkSemaphore> image_available_semaphores_;
    std::vector<VkSemaphore> render_finished_semaphores_;
    std::vector<VkFence> in_flight_fences_;
    bool frame_buffer_resized_ = false;

    const std::vector<const char *> validation_layers_ = {"VK_LAYER_KHRONOS_validation"};
    const std::vector<const char *> device_extensions_ = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
}; // class Chim
} // namespace chim
#endif // CHIM_HPP
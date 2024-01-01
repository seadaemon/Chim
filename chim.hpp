/**
* @file chim.hpp
* @author GP
* @brief Initializes the SDL window and the Vulkan renderer.
*/
#ifndef CHIM_HPP
#define CHIM_HPP
#define SDL_MAIN_HANDLED
#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vulkan/vulkan.hpp>
#include <SDL.h>
#include <SDL_vulkan.h>
//#include <SDL_image.h> //TODO: Fix this import

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif
#define LOG(...) std::cout << __VA_ARGS__ << std::endl

namespace chim {
	/**
	* @class ChimException
	* @brief Exception type for anything in the chim namespace.
	*/
	class ChimException : public std::exception {
	private:
		std::string message_;
	public:
		ChimException(std::string message) : message_("[CHIM Exception] " + message) {};
		virtual const char* what() const throw() { return message_.c_str(); };
		virtual ~ChimException() throw() {};
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	/**
	* @class Chim
	* @brief Renders the main window.
	*/
	class Chim {

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
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& create_info);
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
		bool CheckValidationLayerSupport(void);
		std::vector<const char*> GetRequiredExtensions(void);
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		int RateDeviceSuitability(VkPhysicalDevice device);
		bool IsDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	private:
		const uint32_t window_width_ = 1280;
		const uint32_t window_height_ = 720;
		bool keep_window_open_ = true;
		// SDL
		SDL_Window* window_ = nullptr;
		//SDL_Surface* window_icon_ = nullptr; // TBA
		SDL_Event ev_;
		// Vulkan
		VkInstance instance_;
		VkDebugUtilsMessengerEXT debug_messenger_;
		VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
		VkDevice device_;
		VkQueue graphics_queue_;
		VkSurfaceKHR surface_;
		VkQueue present_queue_;
		const std::vector<const char*> validation_layers_ = { "VK_LAYER_KHRONOS_validation" };
	}; // class Chim
}
#endif //CHIM_HPP
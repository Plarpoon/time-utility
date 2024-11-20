#define GLFW_INCLUDE_VULKAN
#include "main_ui.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

GLFWwindow *create_window(VkInstance *instance, VkSurfaceKHR *surface,
                          uint32_t width, uint32_t height) {
  // Initialize GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return NULL;
  }

  // Configure GLFW for Vulkan
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Create GLFW window
  GLFWwindow *window =
      glfwCreateWindow(width, height, "Vulkan Window", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return NULL;
  }

  // Get required Vulkan extensions
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions =
      glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  // Create Vulkan instance
  VkApplicationInfo appInfo = {
      .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName = "Vulkan GLFW Example",
      .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
      .pEngineName = "No Engine",
      .engineVersion = VK_MAKE_VERSION(1, 0, 0),
      .apiVersion = VK_API_VERSION_1_0,
  };

  VkInstanceCreateInfo createInfo = {
      .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo = &appInfo,
      .enabledExtensionCount = glfwExtensionCount,
      .ppEnabledExtensionNames = glfwExtensions,
  };

  if (vkCreateInstance(&createInfo, NULL, instance) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create Vulkan instance\n");
    glfwDestroyWindow(window);
    glfwTerminate();
    return NULL;
  }

  // Create Vulkan surface
  if (glfwCreateWindowSurface(*instance, window, NULL, surface) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create Vulkan surface\n");
    vkDestroyInstance(*instance, NULL);
    glfwDestroyWindow(window);
    glfwTerminate();
    return NULL;
  }

  return window;
}

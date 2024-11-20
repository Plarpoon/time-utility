#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

GLFWwindow *create_window(VkInstance *instance, VkSurfaceKHR *surface,
                          uint32_t width, uint32_t height);

#endif // MAIN_UI_H

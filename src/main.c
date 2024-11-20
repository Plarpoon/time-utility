#include "main_ui.h"
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    VkInstance instance;
    VkSurfaceKHR surface;
    GLFWwindow* window = create_window(&instance, &surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!window) {
        fprintf(stderr, "Failed to initialize the UI\n");
        return -1;
    }

    printf("Vulkan instance and surface created successfully!\n");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    // Cleanup
    vkDestroySurfaceKHR(instance, surface, NULL);
    vkDestroyInstance(instance, NULL);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

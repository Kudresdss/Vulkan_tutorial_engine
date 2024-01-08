#ifndef VULKAN_TUTORIAL_ENGINE_VKTE_WINDOW_HPP
#define VULKAN_TUTORIAL_ENGINE_VKTE_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//std
#include <string>

namespace vkte {

class VKTEWindow {
public:
    VKTEWindow(int width, int height, std::string name);
    ~VKTEWindow();

    VKTEWindow(const VKTEWindow &) = delete;
    VKTEWindow& operator=(const VKTEWindow &) = delete;

    bool shouldClose() { return glfwWindowShouldClose(glfwWindow); }
    VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; };

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
    void initWindow();

    const int width;
    const int height;

    std::string windowName;
    GLFWwindow *glfwWindow;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VKTE_WINDOW_HPP

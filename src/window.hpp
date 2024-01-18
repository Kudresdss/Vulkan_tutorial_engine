#ifndef VULKAN_TUTORIAL_ENGINE_RENDERER_WINDOW_HPP
#define VULKAN_TUTORIAL_ENGINE_RENDERER_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//std
#include <string>

namespace vkte {

class RendererWindow {
public:
//    RendererWindow() = default;
    RendererWindow(int width, int height, std::string name);
    ~RendererWindow();

    RendererWindow(const RendererWindow &) = delete;
    RendererWindow& operator=(const RendererWindow &) = delete;

    bool shouldClose() { return glfwWindowShouldClose(glfwWindow); }
    bool wasWindowResized() { return framebufferResized; }
    void resetWindowResizedFlag() { framebufferResized = false; }
    VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
    void initWindow();
    static void framebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height);

    int width;
    int height;
    bool framebufferResized{false};

    std::string windowName;
    GLFWwindow *glfwWindow;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_RENDERER_WINDOW_HPP

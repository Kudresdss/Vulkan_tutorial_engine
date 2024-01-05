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

    VKTEWindow(const VKTEWindow&) = delete;
    VKTEWindow& operator=(const VKTEWindow&) = delete;

    bool shouldClose() { return glfwWindowShouldClose(m_glfw_window); }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
    void initWindow();

    const int c_width;
    const int c_height;

    std::string m_window_name;
    GLFWwindow *m_glfw_window;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VKTE_WINDOW_HPP

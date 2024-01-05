#ifndef VULKAN_TUTORIAL_ENGINE_VK_TE_WINDOW_H
#define VULKAN_TUTORIAL_ENGINE_VK_TE_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//std
#include <string>

namespace vk_te {

class VKTEWindow {
public:
    VKTEWindow(int width, int height, std::string name);
    ~VKTEWindow();

    VKTEWindow(const VKTEWindow& w) = delete;
    VKTEWindow& operator=(const VKTEWindow& w) = delete;

    bool shouldClose() { return glfwWindowShouldClose(m_glfw_window); }

private:
    void initWindow();

    const int c_width;
    const int c_height;

    std::string m_window_name;
    GLFWwindow *m_glfw_window;
};

}  // namespace vk_te

#endif  // VULKAN_TUTORIAL_ENGINE_VK_TE_WINDOW_H

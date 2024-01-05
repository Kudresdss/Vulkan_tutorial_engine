#include "vkte_window.hpp"

//std
#include <stdexcept>

namespace vkte {

VKTEWindow::VKTEWindow(
    int width, int height, std::string name) : c_width{width}, c_height{height}, m_window_name{name} {

    initWindow();
}

VKTEWindow::~VKTEWindow() {
    glfwDestroyWindow(m_glfw_window);
    glfwTerminate();
}

void VKTEWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_glfw_window = glfwCreateWindow(c_width, c_height, m_window_name.c_str(), nullptr, nullptr);
}

void VKTEWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, m_glfw_window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }
}

}  // namespace vkte

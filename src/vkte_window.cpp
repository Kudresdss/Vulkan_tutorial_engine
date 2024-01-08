#include "vkte_window.hpp"

//std
#include <stdexcept>

namespace vkte {

VKTEWindow::VKTEWindow(
    int width, int height, std::string name) : width{width}, height{height}, windowName{name} {

    initWindow();
}

VKTEWindow::~VKTEWindow() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

void VKTEWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

void VKTEWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }
}

}  // namespace vkte

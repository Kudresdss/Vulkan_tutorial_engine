#include "window.hpp"

//std
#include <stdexcept>

namespace vkte {

RendererWindow::RendererWindow(
    int width, int height, std::string name) : width{width}, height{height}, windowName{name} {

    initWindow();
}

RendererWindow::~RendererWindow() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

void RendererWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    glfwWindow = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(glfwWindow, this);
    glfwSetFramebufferSizeCallback(glfwWindow, framebufferResizeCallback);
}

void RendererWindow::framebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height) {
    auto vkteWindow = reinterpret_cast<RendererWindow *>(glfwGetWindowUserPointer(glfwWindow));
    vkteWindow->framebufferResized = true;
    vkteWindow->width = width;
    vkteWindow->height = height;
}

void RendererWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, glfwWindow, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }
}

}  // namespace vkte

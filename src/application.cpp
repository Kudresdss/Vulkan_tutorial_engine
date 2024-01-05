#include "application.hpp"

namespace vkte {

void Application::run() {

    while (!m_vkte_window.shouldClose()) {
        glfwPollEvents();
    }
}

}  // namespace vkte

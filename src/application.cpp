#include "application.h"

namespace vk_te {

void Application::run() {

    while (!m_vk_te_window.shouldClose()) {
        glfwPollEvents();
    }
}

}  // namespace vk_te

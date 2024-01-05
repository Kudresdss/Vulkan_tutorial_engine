#ifndef VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H
#define VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

#include "vk_te_window.h"
#include "vk_te_pipeline.h"

namespace vk_te {

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    VKTEWindow m_vk_te_window{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    VKTEPipeline m_vk_te_pipeline{"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv"};
};

}  // namespace vk_te

#endif  // VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

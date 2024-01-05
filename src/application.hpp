#ifndef VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H
#define VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

#include "vkte_pipeline.hpp"
#include "vkte_window.hpp"
#include "vkte_device.hpp"

namespace vkte {

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

private:
    VKTEWindow m_vkte_window{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    VKTEDevice m_vkte_device{m_vkte_window};
    VKTEPipeline m_vkte_pipeline{
        m_vkte_device,
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
        VKTEPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

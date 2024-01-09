#ifndef VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H
#define VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

#include "vkte_pipeline.hpp"
#include "vkte_window.hpp"
#include "vkte_device.hpp"
#include "vkte_swap_chain.hpp"
#include "vkte_model.hpp"

//std
#include <memory>
#include <vector>

namespace vkte {

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Application();
    ~Application();

    Application(const Application &) = delete;
    Application& operator=(const Application &) = delete;

    void run();

private:
    void loadModels();
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();

    void sierpinski(
            std::vector<VKTEModel::Vertex> &vertices,
            int depth,
            glm::vec2 left,
            glm::vec2 right,
            glm::vec2 top);

    VKTEWindow vkteWindow{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    VKTEDevice vkteDevice{vkteWindow};
    VKTESwapChain vkteSwapChain{vkteDevice, vkteWindow.getExtent()};
    std::unique_ptr<VKTEPipeline> vktePipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<VKTEModel> vkteModel;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VTE_APPLICATION_H

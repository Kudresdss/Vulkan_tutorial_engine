#ifndef VULKAN_TUTORIAL_ENGINE_APPLICATION_H
#define VULKAN_TUTORIAL_ENGINE_APPLICATION_H

#include "vkte_pipeline.hpp"
#include "vkte_window.hpp"
#include "vkte_device.hpp"
#include "vkte_swap_chain.hpp"
#include "vkte_model.hpp"
#include "vkte_game_object.hpp"

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
    void loadGameObjects();
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void freeCommandBuffers();
    void drawFrame();
    void renderGameObjects(VkCommandBuffer commandBuffer);

    // Window initial swap chain creation or recreation in case of window resize
    void recreateSwapChain();
    void recordCommandBuffer(int imageIndex);

    RendererWindow rendererWindow{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    Device device{rendererWindow};
    std::unique_ptr<SwapChain> swapChain;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<GameObject> gameObjects;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_APPLICATION_H

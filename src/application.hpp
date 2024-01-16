#ifndef VULKAN_TUTORIAL_ENGINE_APPLICATION_H
#define VULKAN_TUTORIAL_ENGINE_APPLICATION_H

#include "device.hpp"
#include "game_object.hpp"
#include "pipeline.hpp"
#include "renderer.hpp"
#include "window.hpp"

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
    void renderGameObjects(VkCommandBuffer commandBuffer);

    RendererWindow rendererWindow{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    Device device{rendererWindow};
    Renderer renderer{rendererWindow, device};
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<GameObject> gameObjects;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_APPLICATION_H

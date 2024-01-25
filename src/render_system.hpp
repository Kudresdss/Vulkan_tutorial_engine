#ifndef VULKAN_TUTORIAL_ENGINE_RENDER_SYSTEM_HPP
#define VULKAN_TUTORIAL_ENGINE_RENDER_SYSTEM_HPP

#include "camera.hpp"
#include "device.hpp"
#include "frame_info.hpp"
#include "game_object.hpp"
#include "pipeline.hpp"

//std
#include <memory>
#include <vector>

namespace vkte {

class RenderSystem {
public:
    RenderSystem(Device& device, VkRenderPass renderPass);
    ~RenderSystem();

    RenderSystem(const RenderSystem &) = delete;
    RenderSystem& operator=(const RenderSystem &) = delete;

    void renderGameObjects(FrameInfo& frameInfo, std::vector<GameObject>& gameObjects);

private:
    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);

    Device& device;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_RENDER_SYSTEM_HPP

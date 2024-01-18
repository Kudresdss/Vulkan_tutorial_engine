#ifndef VULKAN_TUTORIAL_ENGINE_RENDERER_HPP
#define VULKAN_TUTORIAL_ENGINE_RENDERER_HPP

#include "window.hpp"
#include "device.hpp"
#include "swap_chain.hpp"
#include "model.hpp"

//std
#include <cassert>
#include <memory>
#include <vector>

namespace vkte {

class Renderer {
public:

    Renderer(Device& device, RendererWindow& window);
    ~Renderer();

    Renderer(const Renderer &) = delete;
    Renderer& operator=(const Renderer &) = delete;

    bool isFrameInProgress() const { return isFrameStarted; }
    float getAspectRatio() const { return swapChain->extentAspectRatio(); }
    VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }

    VkCommandBuffer getCurrentCommandBuffer() const {
        assert(isFrameStarted && "Cannot get command buffer when frame is not in progress");
        return commandBuffers[currentFrameIndex];
    }

    int getFrameIndex() const {
        assert(isFrameStarted && "Cannot get frame index when frame is not in progress");
        return currentFrameIndex;
    }

    VkCommandBuffer beginFrame();
    void            endFrame();
    void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
    void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

private:
    void createCommandBuffers();
    void freeCommandBuffers();
    void recreateSwapChain();

    RendererWindow& rendererWindow;
    Device& device;
    std::unique_ptr<SwapChain> swapChain;
    std::vector<VkCommandBuffer> commandBuffers;

    uint32_t currentImageIndex;
    int currentFrameIndex{0};
    bool isFrameStarted{false};
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_RENDERER_HPP

#include "application.hpp"

//std
#include <stdexcept>
#include <array>

namespace vkte {

Application::Application() {
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
}

Application::~Application() {
    vkDestroyPipelineLayout(vkteDevice.device(), pipelineLayout, nullptr);
}

void Application::run() {

    while (!vkteWindow.shouldClose()) {
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(vkteDevice.device());
}

void Application::loadModels() {
    std::vector<VKTEModel::Vertex> vertices {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    vkteModel = std::make_unique<VKTEModel>(vkteDevice, vertices);
}

void Application::createPipelineLayout() {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(vkteDevice.device(),
           &pipelineLayoutInfo,
           nullptr,
           &pipelineLayout) !=
           VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

void Application::recreateSwapChain() {
    auto extent = vkteWindow.getExtent();
    while (extent.width == 0 || extent.height == 0) {  // If any of window's dimensions are zero (during resize) -> wait
        extent = vkteWindow.getExtent();
        glfwWaitEvents();
    }

    vkDeviceWaitIdle(vkteDevice.device());
    if (vkteSwapChain == nullptr) {  // There's no previous swap chain (init or resize)
        vkteSwapChain = std::make_unique<VKTESwapChain>(vkteDevice, extent);
    }
    else {  // There is a previous swap chain
        vkteSwapChain = std::make_unique<VKTESwapChain>(vkteDevice, extent, std::move(vkteSwapChain));
        if (vkteSwapChain->imageCount() != commandBuffers.size()) {  // Old swap chain supports different frame bufferization
            freeCommandBuffers();
            createCommandBuffers();
        }
    }

    createPipeline();  // Future optimization: if render pass is compatible -> do noting
}

void Application::createPipeline() {
    assert(vkteSwapChain != nullptr && "Cannot create pipeline before swap chain");
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfigInfo{};
    VKTEPipeline::setDefaultPipelineConfigInfo(pipelineConfigInfo);
    pipelineConfigInfo.renderPass = vkteSwapChain->getRenderPass();
    pipelineConfigInfo.pipelineLayout = pipelineLayout;
    vktePipeline = std::make_unique<VKTEPipeline>(
            vkteDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfigInfo);
}

void Application::createCommandBuffers() {
    commandBuffers.resize(vkteSwapChain->imageCount());

    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandPool = vkteDevice.getCommandPool();
    allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(
            vkteDevice.device(),
            &allocateInfo,
            commandBuffers.data()) !=
            VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void Application::freeCommandBuffers() {
    vkFreeCommandBuffers(
        vkteDevice.device(),
        vkteDevice.getCommandPool(),
        static_cast<uint32_t>(commandBuffers.size()),
        commandBuffers.data());
    commandBuffers.clear();
}

void Application::drawFrame() {
    uint32_t imageIndex;

    auto result = vkteSwapChain->acquireNextImage(&imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) {  // In case of a window resize error
        recreateSwapChain();
        return;
    }
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    recordCommandBuffer(imageIndex);
    result = vkteSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || vkteWindow.wasWindowResized())  {  // In case of a window resize error
        vkteWindow.resetWindowResizedFlag();
        recreateSwapChain();
        return;
    }
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}

void Application::recordCommandBuffer(int imageIndex) {
    VkCommandBufferBeginInfo commandBufferBeginInfo{};
    commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[imageIndex], &commandBufferBeginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = vkteSwapChain->getRenderPass();
    renderPassBeginInfo.framebuffer = vkteSwapChain->getFrameBuffer(imageIndex);

    renderPassBeginInfo.renderArea.offset = {0, 0};
    renderPassBeginInfo.renderArea.extent = vkteSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassBeginInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(vkteSwapChain->getSwapChainExtent().width);
    viewport.height = static_cast<float>(vkteSwapChain->getSwapChainExtent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    VkRect2D scissor{{0, 0}, vkteSwapChain->getSwapChainExtent()};
    vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
    vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);

    vktePipeline->bind(commandBuffers[imageIndex]);
    vkteModel->bind(commandBuffers[imageIndex]);
    vkteModel->draw(commandBuffers[imageIndex]);

    vkCmdEndRenderPass(commandBuffers[imageIndex]);
    if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

}  // namespace vkte

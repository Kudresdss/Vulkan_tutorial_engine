#include "application.hpp"

//std
#include <stdexcept>
#include <array>

namespace vkte {

Application::Application() {
    loadModels();
    createPipelineLayout();
    createPipeline();
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
        {{0.0f, -0.5f}},
        {{0.5f, 0.5f}},
        {{-0.5f, 0.5f}}
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

void Application::createPipeline() {
    auto pipelineConfigInfo =
        VKTEPipeline::setDefaultPipelineConfigInfo(vkteSwapChain.width(), vkteSwapChain.height());
    pipelineConfigInfo.renderPass = vkteSwapChain.getRenderPass();
    pipelineConfigInfo.pipelineLayout = pipelineLayout;
    vktePipeline = std::make_unique<VKTEPipeline>(
        vkteDevice,
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
        pipelineConfigInfo);
}

void Application::createCommandBuffers() {
    commandBuffers.resize(vkteSwapChain.imageCount());

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

    for (int i = 0; i < commandBuffers.size(); ++i) {
        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[i], &commandBufferBeginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassBeginInfo{};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = vkteSwapChain.getRenderPass();
        renderPassBeginInfo.framebuffer = vkteSwapChain.getFrameBuffer(i);

        renderPassBeginInfo.renderArea.offset = {0, 0};
        renderPassBeginInfo.renderArea.extent = vkteSwapChain.getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};
        renderPassBeginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassBeginInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

        vktePipeline->bind(commandBuffers[i]);
        vkteModel->bind(commandBuffers[i]);
        vkteModel->draw(commandBuffers[i]);

        vkCmdEndRenderPass(commandBuffers[i]);
        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }
}

void Application::drawFrame() {
    uint32_t imageIndex;

    auto result = vkteSwapChain.acquireNextImage(&imageIndex);
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    result = vkteSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }
}

}  // namespace vkte

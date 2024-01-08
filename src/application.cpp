#include "application.hpp"

//std
#include <stdexcept>

namespace vkte {

Application::Application() {
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
    }
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
    auto pipelineConfig =
        VKTEPipeline::setDefaultPipelineConfigInfo(vkteSwapChain.width(), vkteSwapChain.height());
    pipelineConfig.renderPass = vkteSwapChain.getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    vktePipeline = std::make_unique<VKTEPipeline>(
        vkteDevice,
        "shaders/simple_shader.vert.spv",
        "shaders/simple_shader.frag.spv",
        pipelineConfig);
}

void Application::createCommandBuffers() {}

void Application::drawFrame() {}

}  // namespace vkte

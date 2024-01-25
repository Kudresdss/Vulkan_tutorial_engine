#include "render_system.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>

#include <iostream>

namespace vkte {

struct SimplePushConstantData {
    glm::mat4 transform;
    glm::mat4 normalMatrix;
};

RenderSystem::RenderSystem(Device& device, VkRenderPass renderPass) : device{device} {
    createPipelineLayout();
    createPipeline(renderPass);
}

RenderSystem::~RenderSystem() {
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

void RenderSystem::createPipelineLayout() {
    VkPushConstantRange pushConstantRange;
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushConstantData);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(device.device(),
                               &pipelineLayoutInfo,
                               nullptr,
                               &pipelineLayout) !=
        VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
}

void RenderSystem::createPipeline(VkRenderPass renderPass) {
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfigInfo{};
    Pipeline::setDefaultPipelineConfigInfo(pipelineConfigInfo);
    pipelineConfigInfo.renderPass = renderPass;
    pipelineConfigInfo.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(
            device,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfigInfo);
}

void RenderSystem::renderGameObjects(
    VkCommandBuffer commandBuffer,
    std::vector<GameObject>& gameObjects,
    const Camera& camera) {

    pipeline->bind(commandBuffer);

    auto projectionView = camera.getProjection() * camera.getView();

    for (auto& obj : gameObjects) {
        SimplePushConstantData push{};
        auto modelMatrix = obj.transform.mat4();
        push.transform = projectionView * modelMatrix;  // later move camera calc into shader
        push.normalMatrix = obj.transform.normalMatrix();
        vkCmdPushConstants(
                commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push);

        obj.model->bind(commandBuffer);
        obj.model->draw(commandBuffer);
    }
}

}  // namespace vkte
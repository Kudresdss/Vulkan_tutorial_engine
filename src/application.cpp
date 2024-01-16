#include "application.hpp"

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
    glm::mat2 transform{1.f};
    glm::vec2 offset;
    alignas(16) glm::vec3 color;
};

Application::Application() {
    loadGameObjects();
    createPipelineLayout();
    createPipeline();
}

Application::~Application() {
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

void Application::run() {

    std::cout << "maxPushConstanstSize = " << device.properties.limits.maxPushConstantsSize << '\n';

    while (!rendererWindow.shouldClose()) {
        glfwPollEvents();

        // unnecessary branch? - optimize later
        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderGameObjects(commandBuffer);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void Application::loadGameObjects() {
    std::vector<ObjectModel::Vertex> vertices {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    auto model = std::make_shared<ObjectModel>(device, vertices);
    auto triangle = GameObject::createGameObject();
    triangle.model = model;
    triangle.color = {.1f, .8f, .1f};
    triangle.transform2d.translation.x = .2f;
    triangle.transform2d.scale = {2.f, .5f};
    triangle.transform2d.rotation = .25f * glm::two_pi<float>();

    gameObjects.push_back(std::move(triangle));
}

void Application::createPipelineLayout() {
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

void Application::createPipeline() {
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfigInfo{};
    Pipeline::setDefaultPipelineConfigInfo(pipelineConfigInfo);
    pipelineConfigInfo.renderPass = renderer.getSwapChainRenderPass();
    pipelineConfigInfo.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(
            device,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfigInfo);
}

void Application::renderGameObjects(VkCommandBuffer commandBuffer) {
    pipeline->bind(commandBuffer);

    for (auto& obj : gameObjects) {
        obj.transform2d.rotation = glm::mod(obj.transform2d.rotation + .01f, glm::two_pi<float>());

        SimplePushConstantData push{};
        push.offset = obj.transform2d.translation;
        push.color = obj.color;
        push.transform = obj.transform2d.mat2();
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

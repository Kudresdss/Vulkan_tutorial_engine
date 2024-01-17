#include "application.hpp"
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

Application::Application() { loadGameObjects(); }

Application::~Application() {}

void Application::run() {
    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};

    std::cout << "maxPushConstanstSize = " << device.properties.limits.maxPushConstantsSize << '\n';

    while (!rendererWindow.shouldClose()) {
        glfwPollEvents();

        // unnecessary branch? - optimize later
        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects);
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

}  // namespace vkte

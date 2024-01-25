#include "application.hpp"

#include "buffer.hpp"
#include "camera.hpp"
#include "keyboard_movement_controller.hpp"
#include "render_system.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

//std
#include <array>
#include <chrono>
#include <stdexcept>

#include <iostream>

namespace vkte {

struct GlobalUbo {
    glm::mat4 projectionView{1.f};
    glm::vec3 lightDirection = glm::normalize(glm::vec3{1.f, -3.f, -1.f});
};

Application::Application() { loadGameObjects(); }

Application::~Application() {}

void Application::run() {

    Buffer globalUboBuffer{
        device,
        sizeof(GlobalUbo),
        SwapChain::MAX_FRAMES_IN_FLIGHT,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
        device.properties.limits.minUniformBufferOffsetAlignment
    };

    globalUboBuffer.map();

    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};

    Camera camera{};
    camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));
//    camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));

    auto viewerObject = GameObject::createGameObject();
    KeyboardMovementController cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();

    while (!rendererWindow.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        cameraController.moveInPlaneXZ(rendererWindow.getGLFWwindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspect = renderer.getAspectRatio();
        camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
        // camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);

        // unnecessary branch? - optimize later
        if (auto commandBuffer = renderer.beginFrame()) {
            int frameIndex = renderer.getFrameIndex();
            FrameInfo frameInfo{
                frameIndex,
                frameTime,
                commandBuffer,
                camera
            };

            //update
            GlobalUbo ubo{};
            ubo.projectionView = camera.getProjection() * camera.getView();
            globalUboBuffer.writeToIndex(&ubo, frameIndex);
            globalUboBuffer.flush(frameIndex);

            //render
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(frameInfo, gameObjects);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void Application::loadGameObjects() {

    std::shared_ptr<ObjectModel> model = ObjectModel::createModelFromFile(device, "models/flat_vase.obj");
    auto flatVase = GameObject::createGameObject();
    flatVase.model = model;
    flatVase.transform.translation = {-.5f, .5f, 2.5f};
    flatVase.transform.scale = {3.f, 1.5f, 3.f};
    gameObjects.push_back(std::move(flatVase));

    model = ObjectModel::createModelFromFile(device, "models/smooth_vase.obj");
    auto smoothVase = GameObject::createGameObject();
    smoothVase.model = model;
    smoothVase.transform.translation = {.5f, .5f, 2.5f};
    smoothVase.transform.scale = {3.f, 1.5f, 3.f};
    gameObjects.push_back(std::move(smoothVase));
}

}  // namespace vkte

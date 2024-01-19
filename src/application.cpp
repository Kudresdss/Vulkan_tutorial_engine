#include "application.hpp"

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

Application::Application() { loadGameObjects(); }

Application::~Application() {}

void Application::run() {
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
//        camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);

        // unnecessary branch? - optimize later
        if (auto commandBuffer = renderer.beginFrame()) {
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void Application::loadGameObjects() {
    std::shared_ptr<ObjectModel> model = ObjectModel::createModelFromFile(device, "models/colored_cube.obj");

    auto gameObject = GameObject::createGameObject();
    gameObject.model = model;
    gameObject.transform.translation = {.0f, .0f, 2.5f};
    gameObject.transform.scale = {.5f, .5f, .5f};
    gameObjects.push_back(std::move(gameObject));
}

}  // namespace vkte

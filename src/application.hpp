#ifndef VULKAN_TUTORIAL_ENGINE_APPLICATION_HPP
#define VULKAN_TUTORIAL_ENGINE_APPLICATION_HPP

#include "device.hpp"
#include "game_object.hpp"
#include "renderer.hpp"
#include "window.hpp"

//std
#include <memory>
#include <vector>

namespace vkte {

class Application {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    Application();
    ~Application();

    Application(const Application &) = delete;
    Application& operator=(const Application &) = delete;

    void run();

private:
    void loadGameObjects();

    RendererWindow rendererWindow{WIDTH, HEIGHT, "Vulkan tutorial engine"};
    Device device{rendererWindow};
    Renderer renderer{device, rendererWindow};
    std::vector<GameObject> gameObjects;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_APPLICATION_HPP

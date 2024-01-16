#ifndef VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP
#define VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP

#include "model.hpp"

//std
#include <memory>

namespace vkte {

struct Transform2dComponent {
    glm::vec2 translation{};  // position offset
    glm::vec2 scale{1.f, 1.f};
    float rotation;

    glm::mat2 mat2() {
        const float sin = glm::sin(rotation);
        const float cos = glm::cos(rotation);
        glm::mat2 rotationMat{{cos, sin}, {-sin, cos}};

        glm::mat2 scaleMat{{scale.x, .0f}, {.0f, scale.y}};
        return rotationMat * scaleMat; }
};

class GameObject {
public:
    using id_t = unsigned int;

    static GameObject createGameObject() {
        static id_t currentId = 0;
        return GameObject{currentId++};
    }

    GameObject(const GameObject &) = delete;
    GameObject &operator=(const GameObject &) = delete;
    GameObject(GameObject &&) = default;
    GameObject &operator=(GameObject &&) = default;

    id_t getId() { return id; };

    std::shared_ptr<ObjectModel> model{};
    glm::vec3 color{};
    Transform2dComponent transform2d{};

private:
    GameObject(id_t objId) : id{objId} {};

    id_t id;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP

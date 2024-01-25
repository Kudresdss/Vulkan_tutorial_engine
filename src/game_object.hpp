#ifndef VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP
#define VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP

#include "model.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>

//std
#include <memory>

namespace vkte {

struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{1.f, 1.f, 1.f};
    glm::vec3 rotation{};

    // translate * Ry * Rx *Rz * scale affine transformation, optimized version
    glm::mat4 mat4();

    glm::mat3 normalMatrix();
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
    TransformComponent transform{};

private:
    GameObject(id_t objId) : id{objId} {};

    id_t id;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_GAME_OBJECT_HPP

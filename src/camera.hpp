#ifndef VULKAN_TUTORIAL_ENGINE_CAMERA_HPP
#define VULKAN_TUTORIAL_ENGINE_CAMERA_HPP

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace vkte {

class Camera {
public:
    void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);
    void setPerspectiveProjection(float fovY, float aspect, float near, float far);

    const glm::mat4& getProjection() const { return projectionMatrix; }

private:
    glm::mat4 projectionMatrix{1.f};
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_CAMERA_HPP

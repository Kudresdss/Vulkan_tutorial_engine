#ifndef VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP
#define VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP

#include "vkte_device.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//std
#include <vector>

namespace vkte {

class ObjectModel {
public:
    struct Vertex{
        glm::vec2 position;
        glm::vec3 color;

        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
    };

//    ObjectModel() = default;
    ObjectModel(Device& vkteDevice, const std::vector<Vertex> &vertices);
    ~ObjectModel();

    ObjectModel(const ObjectModel &) = delete;
    ObjectModel& operator=(const ObjectModel &) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

private:
    void createVertexBuffers(const std::vector<Vertex> &vertices);

    Device& device;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP

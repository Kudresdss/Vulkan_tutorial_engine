#ifndef VULKAN_TUTORIAL_ENGINE_VKTE_MODEL_HPP
#define VULKAN_TUTORIAL_ENGINE_VKTE_MODEL_HPP

#include "vkte_device.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//std
#include <vector>

namespace vkte {

class VKTEModel {
public:
    struct Vertex{
        glm::vec2 position;

        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
    };

    VKTEModel(VKTEDevice& vkteDevice, const std::vector<Vertex> &vertices);
    ~VKTEModel();

    VKTEModel(const VKTEModel &) = delete;
    VKTEModel& operator=(const VKTEModel &) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

private:
    void createVertexBuffers(const std::vector<Vertex> &vertices);

    VKTEDevice& vkteDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VKTE_MODEL_HPP

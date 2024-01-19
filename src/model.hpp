#ifndef VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP
#define VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP

#include "device.hpp"

//libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

//std
#include <memory>
#include <vector>

namespace vkte {

class ObjectModel {
public:
    struct Vertex{
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal{};
        glm::vec2 uv{};

        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

        bool operator==(const Vertex& other) const {
            return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
        }
    };

    struct Data {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        void loadModel(const std::string& filepath);
    };

//    ObjectModel() = default;
    ObjectModel(Device& device, const ObjectModel::Data& data);
    ~ObjectModel();

    ObjectModel(const ObjectModel &) = delete;
    ObjectModel& operator=(const ObjectModel &) = delete;

    static std::unique_ptr<ObjectModel> createModelFromFile(Device& device, const std::string& filepath);

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

private:
    void createVertexBuffers(const std::vector<Vertex>& vertices);
    void createIndexBuffer(const std::vector<uint32_t>& indices);

    Device& device;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;

    bool hasIndexBuffer = false;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    uint32_t indexCount;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_OBJECT_MODEL_HPP

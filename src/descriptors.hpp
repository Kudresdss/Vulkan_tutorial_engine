#ifndef VULKAN_TUTORIAL_ENGINE_DESCRIPTORS_HPP
#define VULKAN_TUTORIAL_ENGINE_DESCRIPTORS_HPP

#include "device.hpp"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace vkte {

class DescriptorSetLayout {
public:
    class Builder {
    public:
        Builder(Device& device) : device{device} {}

        Builder& addBinding(
                uint32_t binding,
                VkDescriptorType descriptorType,
                VkShaderStageFlags stageFlags,
                uint32_t count = 1);
        std::unique_ptr<DescriptorSetLayout> build() const;

    private:
        Device& device;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
    };

    DescriptorSetLayout(
            Device &device, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
    ~DescriptorSetLayout();
    DescriptorSetLayout(const DescriptorSetLayout &) = delete;
    DescriptorSetLayout &operator=(const DescriptorSetLayout &) = delete;

    VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

private:
    Device &device;
    VkDescriptorSetLayout descriptorSetLayout;
    std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

    friend class LveDescriptorWriter;
};

//class LveDescriptorPool {
//public:
//    class Builder {
//    public:
//        Builder(LveDevice &lveDevice) : lveDevice{lveDevice} {}
//
//        Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);
//        Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);
//        Builder &setMaxSets(uint32_t count);
//        std::unique_ptr<LveDescriptorPool> build() const;
//
//    private:
//        LveDevice &lveDevice;
//        std::vector<VkDescriptorPoolSize> poolSizes{};
//        uint32_t maxSets = 1000;
//        VkDescriptorPoolCreateFlags poolFlags = 0;
//    };
//
//    LveDescriptorPool(
//            LveDevice &lveDevice,
//            uint32_t maxSets,
//            VkDescriptorPoolCreateFlags poolFlags,
//            const std::vector<VkDescriptorPoolSize> &poolSizes);
//    ~LveDescriptorPool();
//    LveDescriptorPool(const LveDescriptorPool &) = delete;
//    LveDescriptorPool &operator=(const LveDescriptorPool &) = delete;
//
//    bool allocateDescriptor(
//            const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;
//
//    void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;
//
//    void resetPool();
//
//private:
//    LveDevice &lveDevice;
//    VkDescriptorPool descriptorPool;
//
//    friend class LveDescriptorWriter;
//};
//
//class LveDescriptorWriter {
//public:
//    LveDescriptorWriter(LveDescriptorSetLayout &setLayout, LveDescriptorPool &pool);
//
//    LveDescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);
//    LveDescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);
//
//    bool build(VkDescriptorSet &set);
//    void overwrite(VkDescriptorSet &set);
//
//private:
//    LveDescriptorSetLayout &setLayout;
//    LveDescriptorPool &pool;
//    std::vector<VkWriteDescriptorSet> writes;
//};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_DESCRIPTORS_HPP
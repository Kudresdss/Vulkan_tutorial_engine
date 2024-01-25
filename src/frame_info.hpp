#ifndef VULKAN_TUTORIAL_ENGINE_FRAME_INFO_HPP
#define VULKAN_TUTORIAL_ENGINE_FRAME_INFO_HPP

#include "camera.hpp"

//lib
#include <vulkan/vulkan.h>

namespace vkte {

struct FrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    Camera& camera;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_FRAME_INFO_HPP

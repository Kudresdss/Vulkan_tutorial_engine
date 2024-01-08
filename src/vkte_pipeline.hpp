#ifndef VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP
#define VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP

#include "vkte_device.hpp"

//std
#include <string>
#include <vector>

namespace vkte {

struct PipelineConfigInfo {
    VkViewport viewport;
    VkRect2D scissor;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class VKTEPipeline {
public:
    VKTEPipeline(
            VKTEDevice& device,
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);
    ~VKTEPipeline();

    VKTEPipeline(const VKTEPipeline &) = delete;
    VKTEPipeline& operator=(const VKTEPipeline &) = delete;

    static PipelineConfigInfo setDefaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath,
                                const std::string& fragFilepath,
                                const PipelineConfigInfo& configInfo);

    void createShaderModule(const std::vector<char>& code, VkShaderModule *shaderModule);

    VKTEDevice& vkteDevice;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP

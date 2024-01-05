#ifndef VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP
#define VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP

#include "vkte_device.hpp"

//std
#include <string>
#include <vector>

namespace vkte {

struct PipelineConfigInfo {

};

class VKTEPipeline {
public:
    VKTEPipeline(
            VKTEDevice& device,
            const std::string& vertFilepath,
            const std::string& fragFilepath,
            const PipelineConfigInfo& configInfo);
    ~VKTEPipeline() {};

    VKTEPipeline(const VKTEPipeline&) = delete;
    void operator=(const VKTEPipeline&) = delete;

    static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath,
                                const std::string& fragFilepath,
                                const PipelineConfigInfo& configInfo);

    void createShaderModule(const std::vector<char>& code, VkShaderModule *shaderModule);

    VKTEDevice& m_vkte_device;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
};

}  // namespace vkte

#endif  // VULKAN_TUTORIAL_ENGINE_VKTE_PIPELINE_HPP

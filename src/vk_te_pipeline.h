#ifndef VULKAN_TUTORIAL_ENGINE_VK_TE_PIPELINE_H
#define VULKAN_TUTORIAL_ENGINE_VK_TE_PIPELINE_H

//std
#include <string>
#include <vector>

namespace vk_te {

class VKTEPipeline {
public:
    VKTEPipeline(const std::string& vertFilepath, const std::string& fragFilepath);

private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);
};

}  // namespace vk_te

#endif  // VULKAN_TUTORIAL_ENGINE_VK_TE_PIPELINE_H

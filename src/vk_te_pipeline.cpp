#include "vk_te_pipeline.h"

//std
#include <fstream>
#include <stdexcept>

#include <iostream>

namespace vk_te {

VKTEPipeline::VKTEPipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
    createGraphicsPipeline(vertFilepath, fragFilepath);
}

std::vector<char> VKTEPipeline::readFile(const std::string& filepath) {

    std::ifstream file{filepath, std::ios::ate | std::ios::binary};

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

void VKTEPipeline::createGraphicsPipeline(
    const std::string& vertFilepath, const std::string& fragFilepath) {

    std::vector<char> vertCode = readFile(vertFilepath);
    std::vector<char> fragCode = readFile(fragFilepath);
}

}  // namespace vk_te

VULKAN_SDK = /Users/Ivan/VulkanSDK/1.3.268.1/macOS
GLSL = /usr/local/bin/glslc
TINY_OBJECT_LOADER = ./libs/tiny_object_loader

CFLAGS = -std=c++20 -I. -I$(VULKAN_SDK)/include -I$(TINY_OBJECT_LOADER)
LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan

vertSrcFiles = $(shell find ./shaders -type f -name "*.vert")
vertObjFiles = $(patsubst %.vert, %.vert.spv, $(vertSrcFiles))
fragSrcFiles = $(shell find ./shaders -type f -name "*.frag")
fragObjFiles = $(patsubst %.frag, %.frag.spv, $(fragSrcFiles))

TARGET = a.out
$(TARGET): $(vertObjFiles) $(fragObjFiles)
$(TARGET): *.cpp *.hpp
	g++ $(CFLAGS) -o a.out *.cpp $(LDFLAGS)

%.spv: %
	${GLSL} $< -o $@

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out

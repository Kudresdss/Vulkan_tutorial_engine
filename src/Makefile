VULKAN_SDK = /Users/Ivan/VulkanSDK/1.3.268.1/macOS

CFLAGS = -std=c++20 -I. -I$(VULKAN_SDK)/include
LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan

a.out: *.cpp *.h
	g++ $(CFLAGS) -o a.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out

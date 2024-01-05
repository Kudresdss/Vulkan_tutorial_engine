cmake_minimum_required(VERSION 3.5)
project(Vulkan_tutorial_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(COVERAGE_COMPILE_FLAGS "--coverage")
#set(COVERAGE_LINKER_FLAGS "--coverage")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(PROJECT_DIRS
        .
        )

#set(TEST_DIRS
#        test
#        )
#set(TEST_EXECUTABLE tests)

include_directories(/usr/local/lib)
include_directories(/usr/local/include)

find_package(glfw3 3.3 REQUIRED)

#find_package(GTest REQUIRED)
#
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
#        DOWNLOAD_NO_EXTRACT TRUE
#)
#FetchContent_MakeAvailable(googletest)


foreach(dir ${PROJECT_DIRS})
    file(GLOB CC_SOURCES "${dir}/*.cc")
    file(GLOB CPP_SOURCES "${dir}/*.cpp")
    file(GLOB HEADER_H_SOURCES "${dir}/*.h")
    file(GLOB HEADER_HPP_SOURCES "${dir}/*.hpp")
    list(APPEND PROJECT_SOURCES ${CC_SOURCES} ${CPP_SOURCES} ${HEADER_H_SOURCES} ${HEADER_HPP_SOURCES})
endforeach()

#foreach(dir ${TEST_DIRS})
#    file(GLOB CC_SOURCES "${dir}/*.cc")
#    file(GLOB CPP_SOURCES "${dir}/*.cpp")
#    file(GLOB HEADER_H_SOURCES "${dir}/*.h")
#    file(GLOB HEADER_HPP_SOURCES "${dir}/*.hpp")
#    list(APPEND TEST_SOURCES ${CC_SOURCES} ${CPP_SOURCES} ${HEADER_H_SOURCES} ${HEADER_HPP_SOURCES})
#endforeach()

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/model)
#target_include_directories(${TEST_EXECUTABLE} PRIVATE ${CMAKE_SOURCE_DIR}/model)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/view)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/controller)

target_link_libraries(${PROJECT_NAME} glfw)
#target_link_libraries(${TEST_EXECUTABLE} PRIVATE ${GTEST_LIBRARIES} pthread)

#target_compile_options(${TEST_EXECUTABLE} PRIVATE ${COVERAGE_COMPILE_FLAGS})
#target_link_options(${TEST_EXECUTABLE} PRIVATE ${COVERAGE_LINKER_FLAGS})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#        MACOSX_BUNDLE TRUE
#        WIN32_EXECUTABLE TRUE
#        )

#install(TARGETS ${PROJECT_NAME}
#        BUNDLE DESTINATION ..
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

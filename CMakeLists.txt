cmake_minimum_required(VERSION 3.0)
project(Engine)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(Engine/vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(Engine/vendor/assimp)


if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /source-charset:utf-8 /execution-charset:gbk")
    add_definitions(-DGU_WINDOWS_MSVC)
else()
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-parentheses  -std=c++11")
        message("Apple")
    elseif(WIN32)
        message("WIN32")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-parenthese -fexec-charset=GBK  -std=c++11")
    elseif(UNIX AND NOT APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wpedantic  -std=c++11")
        message("Linux")        
    endif()
    
        
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()


configure_file (
    "${PROJECT_SOURCE_DIR}/Engine/configuration/rw_config.h.in"
    "${PROJECT_SOURCE_DIR}/Engine/include/rw_config.h"
)

include_directories(                Engine/include/
                                    Engine/vendor/glad/include/
                                    Engine/vendor/glfw/include/
                                    Engine/vendor/stb
                                    Engine/vendor/glm
                                    Engine/vendor/imgui
                                    Engine/vendor/assimp/include/
                                    )

file(GLOB VENDORS_SOURCES           Engine/vendor/glad/src/glad.c
                                    Engine/vendor/imgui/*.cpp
                                    Engine/vendor/imgui/backends/imgui_impl_opengl3.cpp
                                    Engine/vendor/imgui/backends/imgui_impl_glfw.cpp
                                    )
file(GLOB PROJECT_HEADERS           Engine/include/*.hpp
                                    Engine/include/*.h
                                    Engine/test/*.h
                                    )
file(GLOB PROJECT_SOURCES           Engine/src/*.cpp
                                    Engine/test/*.cpp
                                    # test/*.cpp
                                    )

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
                -DASSIMP_BUILD_ASSIMP_TOOLS="OFF")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      )

# target_link_libraries(test ${PROJECT_NAME} assimp glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# set_target_properties(test PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)  # 设置test项目的输出路径

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Engine/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/)

cmake_minimum_required(VERSION 3.0)

add_subdirectory(test)

# add_library(Engine ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDORS_SOURCES})
# target_link_libraries(Engine assimp glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

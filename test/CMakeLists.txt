cmake_minimum_required(VERSION 3.0)
project(EngineTest)

include_directories(                ../Engine/include/
                                    ../Engine/vendor/glad/include/
                                    ../Engine/vendor/glfw/include/
                                    ../Engine/vendor/stb
                                    ../Engine/vendor/glm
                                    ../Engine/vendor/imgui
                                    ../Engine/vendor/assimp/include/
                                    )

file(GLOB VENDORS_SOURCES           ../Engine/vendor/glad/src/glad.c
                                    ../Engine/vendor/imgui/*.cpp
                                    ../Engine/vendor/imgui/backends/imgui_impl_opengl3.cpp
                                    ../Engine/vendor/imgui/backends/imgui_impl_glfw.cpp
                                    )
file(GLOB PROJECT_HEADERS           ../Engine/include/*.hpp
                                    ../Engine/include/*.h
                                    # ../Engine/test/*.h
                                    )
file(GLOB PROJECT_SOURCES           ../Engine/src/*.cpp
                                    # ../Engine/test/*.cpp
                                    *.cpp
                                    )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      )

# add_executable(${PROJECT_NAME} "main.cpp")
# target_link_libraries(${PROJECT_NAME} Engine)


# Minimum CMake version
cmake_minimum_required(VERSION 3.17)

# Project name
project(pong)

# Use the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Path aliases
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# List of source files to compile
set(SOURCE
    ${SOURCE_DIR}/Ball.cpp
    ${SOURCE_DIR}/Entity.cpp
    ${SOURCE_DIR}/Game.cpp
    ${SOURCE_DIR}/IndexBuffer.cpp
    ${SOURCE_DIR}/IntroState.cpp
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/MenuState.cpp
    ${SOURCE_DIR}/PlayState.cpp
    ${SOURCE_DIR}/Renderable.cpp
    ${SOURCE_DIR}/Renderer.cpp
    ${SOURCE_DIR}/Shader.cpp
    ${SOURCE_DIR}/Sprite.cpp
    ${SOURCE_DIR}/TextRenderer.cpp
    ${SOURCE_DIR}/VertexArray.cpp
    ${SOURCE_DIR}/VertexBuffer.cpp
    ${SOURCE_DIR}/Window.cpp
)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCE})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${LIBRARIES_DIR}/glfw EXCLUDE_FROM_ALL)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Glad
add_subdirectory(${LIBRARIES_DIR}/glad EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# Glm
add_subdirectory(${LIBRARIES_DIR}/glm EXCLUDE_FROM_ALL)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)

# Freetype2
set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
add_subdirectory(${LIBRARIES_DIR}/freetype2 EXCLUDE_FROM_ALL)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBRARIES_DIR}/freetype2/include)
target_link_libraries(${PROJECT_NAME} PRIVATE freetype)

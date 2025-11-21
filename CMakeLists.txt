cmake_minimum_required(VERSION 3.10)
project(BlackHoleSimulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Prefer GLVND (modern) over legacy OpenGL libraries
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Find dependencies via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

# GLM is header-only, so we try pkg-config but don't require it
pkg_check_modules(GLM glm)

# Find OpenGL using standard CMake module as fallback
find_package(OpenGL REQUIRED)

include_directories(
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/imgui
)

link_directories(
    ${GLEW_LIBRARY_DIRS}
    ${GLFW_LIBRARY_DIRS}
)

file(GLOB IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
)

add_executable(blackhole_sim
    src/main.cpp
    src/renderer.cpp
    src/physics.cpp
    src/camera.cpp
    src/blackhole.cpp
    src/object.cpp
    src/shader.cpp
    ${IMGUI_SOURCES}
)

target_link_libraries(blackhole_sim
    OpenGL::GL
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    X11
    pthread
    Xrandr
    Xi
    dl
)

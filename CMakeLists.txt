cmake_minimum_required(VERSION 3.28)
project(opengl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(GLAD STATIC glad/src/glad.c)
target_include_directories(GLAD PUBLIC glad/include)

set(LIB_LINKS
        glfw
        GLAD
        glm
        ${OPENGL_LIBRARIES})

file(COPY_FILE main.vert ${CMAKE_CURRENT_BINARY_DIR}/main.vert)
file(COPY_FILE main.frag ${CMAKE_CURRENT_BINARY_DIR}/main.frag)
add_executable(opengl_template main.cpp
        shader.h
        object.cpp
        object.h
        Camera.cpp
        Camera.h)
target_link_libraries(opengl_template ${LIB_LINKS})

cmake_minimum_required(VERSION 3.27.7)

project(AudioProject)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp src/audioobject.cpp src/include/sdl/sdlaudiocontext.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE -g -lSDL2)

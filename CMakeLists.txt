cmake_minimum_required(VERSION 3.10.2)

project(wasm_sdk_test)

find_package(OpenCV 3 REQUIRED)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --bind -s DEMANGLE_SUPPORT=1 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g --bind -s DEMANGLE_SUPPORT=1 -s ALLOW_MEMORY_GROWTH=1 ")


include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(main main.cpp)
target_link_libraries(main  ${OpenCV_LIBS})

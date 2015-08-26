cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
project(GRAVITATION)
set(version 0.1.0)

find_package(gravitation REQUIRED)

include_directories(${GRAVITATION_INCLUDE_DIRS})

# Create executable.
add_executable(gravitation-example main.cxx)
target_link_libraries(gravitation-example ${GRAVITATION_LIBRARIES})

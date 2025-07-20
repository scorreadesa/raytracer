cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(raycasting main.cpp)

target_link_libraries(raycasting Boost::program_options)
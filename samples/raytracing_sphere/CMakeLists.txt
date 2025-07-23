cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(raytracing_sphere main.cpp)

target_link_libraries(raytracing_sphere Boost::program_options)
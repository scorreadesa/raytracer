if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(raycasting main.cpp)

target_link_libraries(raycasting Boost::program_options)
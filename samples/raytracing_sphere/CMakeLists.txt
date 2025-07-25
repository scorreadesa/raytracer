cmake_policy(SET CMP0167 NEW)

include(FetchContent)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG        yaml-cpp-0.7.0
)

FetchContent_MakeAvailable(yaml-cpp)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(raytracing_sphere main.cpp)

target_link_libraries(raytracing_sphere Boost::program_options yaml-cpp)
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(drawclock main.cpp)

target_link_libraries(drawclock Boost::program_options)
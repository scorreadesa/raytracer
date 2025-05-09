cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(trajectory main.cpp
        ../../include/drawing.hpp
        ../../include/exceptions.hpp
        ../../include/IFileWriter.hpp
        ../../include/PPMFileWriter.h
        ../../include/FileWriter.hpp
        ../../include/maths.hpp
)

target_link_libraries(trajectory Boost::program_options)

cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(circulargradient main.cpp
        ../../include/drawing.hpp
        ../../include/exceptions.hpp
        ../../include/IFileWriter.hpp
        ../../include/PPMFileWriter.hpp
        ../../include/FileWriter.hpp
        ../../include/maths.hpp
)

target_link_libraries(circulargradient Boost::program_options)
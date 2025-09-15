cmake_policy(SET CMP0167 NEW)

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(pridecanvas main.cpp
        ../../include/drawing.hpp
        ../../include/Exceptions.hpp
        ../../include/IFileWriter.hpp
        ../../include/PPMFileWriter.hpp
        ../../include/FileWriter.hpp
        ../../include/maths.hpp
)

target_link_libraries(pridecanvas Boost::program_options)
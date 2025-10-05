if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(trajectory main.cpp
        ../../include/drawing.hpp
        ../../include/Exceptions.hpp
        ../../include/IFileWriter.hpp
        ../../include/PPMFileWriter.hpp
        ../../include/FileWriter.hpp
        ../../include/maths.hpp
)

target_link_libraries(trajectory Boost::program_options)

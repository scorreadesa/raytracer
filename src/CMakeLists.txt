add_executable(raytracer main.cpp
        maths.cpp
        ../include/drawing.hpp
        exceptions.cpp
        ../include/exceptions.hpp
        ../include/IFileWriter.hpp
        PPMFileWriter.cpp
        ../include/PPMFileWriter.h
        ../include/FileWriter.hpp
)

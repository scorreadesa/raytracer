include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()

# Set up the raytracer_tests executable
add_executable(raytracer_tests raytracer_tests.cpp
        ../include/maths.hpp
        ../include/drawing.hpp
        ../include/IFileWriter.hpp
        ../include/PPMFileWriter.hpp
        ../include/FileWriter.hpp)


target_link_libraries(raytracer_tests GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(raytracer_tests)

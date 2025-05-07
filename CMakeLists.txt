cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(tests)

file(GLOB SAMPLE_DIRS RELATIVE ${CMAKE_SOURCE_DIR}/samples ${CMAKE_SOURCE_DIR}/samples/*)
foreach (dir ${SAMPLE_DIRS})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/samples/${dir})
        if(EXISTS ${CMAKE_SOURCE_DIR}/samples/${dir}/CMakeLists.txt)
            message(STATUS "Adding: ${dir}")
            add_subdirectory(samples/${dir})
        endif()
    endif()
endforeach()
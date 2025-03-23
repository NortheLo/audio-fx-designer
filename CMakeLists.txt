cmake_minimum_required(VERSION 3.26)
project(audio-fx-designer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure that the compiler warnings are set correctly
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wnull-dereference")

# Specify separate flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET "gtkmm-4.0")
pkg_check_modules(GLIBMM REQUIRED IMPORTED_TARGET "glibmm-2.68")

find_package(Catch2 3 REQUIRED)

# Function to create executables with Catch2 linked
function(add_test_executable target_name)
    add_executable(${target_name} ${ARGN})
    target_link_libraries(${target_name} PRIVATE Catch2::Catch2WithMain)
endfunction()

# Add test executables
add_test_executable(SignalFuncTest tests/SignalFuncTest.cpp src/FuncGenerator.cpp)
add_test_executable(FilterTest tests/FilterTest.cpp src/Filter.cpp src/FuncGenerator.cpp)

# Add the main application executable
add_executable(audio-fx-designer src/main.cpp src/AudioSystem.cpp src/WavWriter.cpp src/FDNReverb.cpp src/FuncGenerator.cpp)
target_link_libraries(audio-fx-designer PRIVATE -lportaudio PkgConfig::GTKMM PkgConfig::GLIBMM)

# Organize output directories for builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Optionally enable testing if Catch2 is found
include(CTest)
if(CATCH2_FOUND)
    enable_testing()
    add_test(NAME SignalFuncTest COMMAND SignalFuncTest)
    add_test(NAME FilterTest COMMAND FilterTest)
endif()

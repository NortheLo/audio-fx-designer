cmake_minimum_required(VERSION 3.26)
project(audio-fx-designer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET "gtkmm-4.0")
pkg_check_modules(GLIBMM REQUIRED IMPORTED_TARGET "glibmm-2.68")

add_executable(audio-fx-designer src/main.cpp src/AudioSystem.cpp src/WavWriter.cpp src/FDNReverb.cpp src/FuncGenerator.cpp) # src/Delay.cpp src/ProceduralReverb.cpp, src/Window.cpp src/DropDown.cpp src/LowPass.cpp)
target_link_libraries(audio-fx-designer -lportaudio PkgConfig::GTKMM PkgConfig::GLIBMM)
add_compile_options(CMAKE_CXX_FLAGS -Wall -Wextra -Werror Wpedantic)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

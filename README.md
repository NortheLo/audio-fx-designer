# About  
This project should be a simple program, which reads input from an input device like your soundcard and apply your implemented audio effect and route it back to a desired output. 

# Features
- Routing of audio samples from any audio device (cross platform)
- Signal Functions to inspect and test DSP implementation
- Wav Filewriter to export samples to e.g. MATLAB/Octave/Python
- MATLAB/Octave Scripts for debuging of C++ DSP implementations

## Build
Step 1: Create build directory  ``mkdir build && cd build``  
Step 2: Create makefile and build with   ``cmake .. && make`` 
Step 3: Install the testing library Catch2 in the libs/ directory. 

## To-Do:
### Build:
 - [x] Add CMake Flags for Release Mode with -O2/-O3 Optimization  

### Audio Effect:
 - [x] Implement simple reverb algorithm

### FX Design Utilities
 - [x] Simple MATLAB/Octave Script to read .wav

### GUI: 
 - [ ] Design Main-Window with Glade to tune paramters in realtime
 - [ ] Implement in-/output device selector

## Dependencies:
All of the dependencies should be included in your distributors repos since all of them are quite standard packages for audio and gui programs. On OpenBSD those packages should be available under x11/ and audio/.
 - PortAudio -> should be available as portaudio(-devel)
 - libasan for Debug build 
 - gtkmm & glibmm (unused right now)

 ## Latency
 For low-latency you have to generate the Makefile with ``cmake .. -DCMAKE_BUILD_TYPE=Release``. Otherwise one will experience noticeable latency.
 

cmake_minimum_required(VERSION 3.12)
project(HFT_Terminal_App)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add header files to the include path
include_directories(include)

# Create the executable
add_executable(
    hft_app
    main.cpp
    src/Strategy.cpp
)

# Optional: Add compiler flags for optimization in release mode
target_compile_options(hft_app PRIVATE
    $<$<CONFIG:Release>:-O3>
)
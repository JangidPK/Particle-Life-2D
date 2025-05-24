cmake_minimum_required(VERSION 3.16)

project(differentTyepOfHardSphere)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the SFML package
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

# Recursively find all source files in the src directory
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Create an executable from the source files
add_executable(app ${SRC_FILES})

# Link the SFML libraries to the executable
target_link_libraries(app sfml-graphics sfml-audio sfml-window sfml-system)

# Include directories
target_include_directories(app
    PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

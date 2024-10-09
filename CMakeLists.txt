# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(PSO-X VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES
    "src/*.cpp"
    "src/Functions/*.cpp"
)

# Add main executable with all found source files
# Add source directory
add_executable(PSO-X ${SOURCES})

# Find GSL package
find_package(GSL REQUIRED)

# Include header files directory
target_include_directories(PSO-X PUBLIC
    src
    ${GSL_INCLUDE_DIRS}
    src/Functions
)

# Link GSL to the executable
target_link_libraries(PSO-X PRIVATE
    ${GSL_LIBRARIES}      # Link against the GSL libraries
)


# add_custom_command(
#     TARGET PSO-X POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/supportData $<TARGET_FILE_DIR:PSO-X>/supportData
# )

# Add any additional libraries if required
# For example: target_link_libraries(MyProject PRIVATE some_library)

# Set output directories
set_target_properties(PSO-X PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
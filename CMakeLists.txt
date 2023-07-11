cmake_minimum_required(VERSION 3.0)
project(VigenereCipher)

# Set the source file and its directory
set(SOURCE_DIR src)
set(SOURCE_FILES 
    ${SOURCE_DIR}/encoding.c
    ${SOURCE_DIR}/main.c
)

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
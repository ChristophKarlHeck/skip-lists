
cmake_minimum_required(VERSION 3.16)

project(SkipLists VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add executable target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/DetSkipLists.cpp
    src/SkipListNode.cpp
    src/utils.cpp
)

# Link libraries (if needed, update accordingly)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
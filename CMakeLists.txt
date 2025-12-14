cmake_minimum_required(VERSION 3.20)
project(gameengine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Find SDL2 using pkg-config with IMPORTED_TARGET
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_TTF REQUIRED IMPORTED_TARGET SDL2_ttf)
pkg_check_modules(LUA REQUIRED IMPORTED_TARGET lua)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES}
        src/Systems/MovementSystem.cpp
        src/Systems/MovementSystem.h)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/libs
)

# Link libraries using imported targets
target_link_libraries(${PROJECT_NAME}
    PkgConfig::SDL2
    PkgConfig::SDL2_IMAGE
    PkgConfig::SDL2_MIXER
    PkgConfig::SDL2_TTF
    PkgConfig::LUA
)

# Add compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE SOL_ALL_SAFETIES_ON=1)

# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Collect test source files (excluding main.cpp from src)
file(GLOB TEST_SOURCES "tests/*.cpp")

# Collect all ECS and Component source files for the test executable
file(GLOB ECS_SOURCES "src/ECS/*.cpp")
file(GLOB COMPONENT_SOURCES "src/Components/*.cpp")

# Create test executable
add_executable(run_tests
    ${TEST_SOURCES}
    ${ECS_SOURCES}
    ${COMPONENT_SOURCES}
        src/Components/RigidBody.h
)

# Include directories for tests
target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs
    ${GTEST_INCLUDE_DIRS}
)

# Link Google Test and other necessary libraries
target_link_libraries(run_tests
    GTest::gtest
    GTest::gtest_main
    PkgConfig::SDL2
    PkgConfig::LUA
)

# Discover tests
gtest_discover_tests(run_tests)

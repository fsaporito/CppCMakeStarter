# Set the project name and language
project(MYPROJECT LANGUAGES C CXX)

# CMake Minimum Version
cmake_minimum_required(VERSION 3.16)

# Check Requirements (Languages, Cmake, Compiler)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake Options
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Custom Options
option(ENABLE_CONAN "Enable conan for dependency management" ON)
option(ENABLE_TESTING "enable unit tests" ON)
option(USE_LTO "Add LTO optimization to Release build" ON)
option(STATIC_ANALYZER_CLANG_TIDY "Enable include-what-you-use static analyzer" OFF)
option(STATIC_ANALYZER_CPPCHECK "Enable clang-tidy static analyzer" OFF)
option(STATIC_ANALYZER_IWYU "Enable cppcheck static analyzer" OFF)
option(STATIC_ANALYZER_VISUAL_STUDIO "Enable visual studio static analyzer" OFF)
option(WARNINGS_AS_ERRORS "treat warnings as errors" OFF)

# CMake modules & includes
set(CMAKE_CUSTOM_MODULES_PATH ${CMAKE_CUSTOM_MODULES_PATH} ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CUSTOM_MODULES_PATH}")
include(${CMAKE_CUSTOM_MODULES_PATH}/index.cmake)

# Set Warnings
create_warnings_list(C_WARNINGS_LIST CXX_WARNINGS_LIST WARNINGS_AS_ERRORS)
message("-- C Warnings: " ${C_WARNINGS_LIST})
message("-- C++ Warnings: " ${CXX_WARNINGS_LIST})

# Set Build Type and Optimization Settings
create_optimization_flags(USE_LTO OPTIMIZATION_SETTINGS)
message("-- Build Type: " ${CMAKE_BUILD_TYPE})
message("-- Optimization Settings: " ${OPTIMIZATION_SETTINGS})

# Configuration Target with all the warnings and optimizations
add_library(ProjectConfiguration INTERFACE)
target_compile_options(
  ProjectConfiguration
  INTERFACE # Optimization Settigs
  ${OPTIMIZATION_SETTINGS}

  # C++ warnings
  $<$<COMPILE_LANGUAGE:CXX>:${CXX_WARNINGS_LIST}>

  # C warnings
  $<$<COMPILE_LANGUAGE:C>:${C_WARNINGS_LIST}>)

# Static Analyzers
message("-- Clang-Tidy Static Analyzer is Active: " ${STATIC_ANALYZER_CLANG_TIDY})
message("-- CPPCHECK Static Analyzer is Active: " ${STATIC_ANALYZER_CPPCHECK})
message("-- IWYU Static Analyzer is Active: " ${STATIC_ANALYZER_IWYU})
message("-- Visual Studio Static Analysis is Active: " ${STATIC_ANALYZER_VISUAL_STUDIO})
enable_static_analysis(STATIC_ANALYZER_CLANG_TIDY STATIC_ANALYZER_CPPCHECK STATIC_ANALYZER_IWYU
  STATIC_ANALYZER_VISUAL_STUDIO)

# Conan Configuration & Dependencies install
if(ENABLE_CONAN)
  include(${CMAKE_CUSTOM_MODULES_PATH}/conan_config.cmake)
endif()

# Source Code
message("Building Src")
add_subdirectory(src)

# Tests
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

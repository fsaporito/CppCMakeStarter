cmake_minimum_required(VERSION 3.15)

# Set the project name
project(myproject CXX)


# General Project Settings
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)


# Fake Library to link for setting the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)


# Fake Library to link for warnings parameters
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)


# Enable cache system
include(cmake/Cache.cmake)


# Sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)


# Doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()


# Static Analysis
include(cmake/StaticAnalyzers.cmake)


option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)


# PCH
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if(ENABLE_PCH)
  target_precompile_headers(
    project_options
    INTERFACE
    <vector>
    <string>
    <map>)
endif()


# Conan for Dependency Management
option(ENABLE_CONAN "Use Conan for dependency management" ON)
if(ENABLE_CONAN)
  include(cmake/Conan.cmake)
  run_conan()
endif()


# Unit Testing
option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests")
  add_subdirectory(test)
endif()



# Source Code
add_subdirectory(src)

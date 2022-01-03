option(USE_LIB_1 "Enable compilation of LIB1" ON)
option(USE_LIB_2 "Enable compilation of LIB2" OFF)

# lib1
if(USE_LIB_1)
  message("Using lib1")
  add_subdirectory(lib1)
endif()

# lib2
if(USE_LIB_1)
  message("Using lib2")
  add_subdirectory(lib2)
endif()

find_package(fmt)
find_package(spdlog)
find_package(docopt)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)

find_package(Catch2 REQUIRED)

include(CTest)
include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

include_directories(../src)

add_subdirectory(prime_test)
add_subdirectory(factorial_test)
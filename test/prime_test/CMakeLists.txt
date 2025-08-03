add_executable(prime_test prime_tests.cpp)
target_link_libraries(prime_test PRIVATE ProjectConfiguration Catch2::Catch2WithMain prime)
message(STATUS "Target PRIME_TEST created successfully")

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
    prime_test
    TEST_PREFIX
    "unittests."
    REPORTER
    XML
    OUTPUT_DIR
    .
    OUTPUT_PREFIX
    "unittests."
    OUTPUT_SUFFIX
    .xml)

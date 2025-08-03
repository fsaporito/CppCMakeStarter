#include "factorial/factorial.h"
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Factorials are computed: 0!", "[computeFact0]")
{
    REQUIRE(factorial::computeFact(0) == 1);
}

TEST_CASE("Factorials are computed: 1!", "[computeFact1]")
{
    REQUIRE(factorial::computeFact(1) == 1);
}

TEST_CASE("Factorials are computed: 2!", "[computeFact2]")
{
    REQUIRE(factorial::computeFact(2) == 2);
}

TEST_CASE("Factorials are computed: 3!", "[computeFact3]")
{
    REQUIRE(factorial::computeFact(3) == 6);
}

TEST_CASE("Factorials are computed: 4!", "[computeFact4]")
{
    REQUIRE(factorial::computeFact(4) == 24);
}

TEST_CASE("Factorials are computed: 5!", "[computeFact5]")
{
    REQUIRE(factorial::computeFact(5) == 120);
}

TEST_CASE("Factorials are computed: 6!", "[computeFact6]")
{
    REQUIRE(factorial::computeFact(6) == 720);
}

TEST_CASE("Factorials are computed: 7!", "[computeFact7]")
{
    REQUIRE(factorial::computeFact(7) == 5040);
}

TEST_CASE("Factorials are computed: 8!", "[computeFact8]")
{
    REQUIRE(factorial::computeFact(8) == 40320);
}

TEST_CASE("Factorials are computed: 9!", "[computeFact9]")
{
    REQUIRE(factorial::computeFact(9) == 362880);
}

TEST_CASE("Factorials are computed: 10!", "[computeFact10]")
{
    REQUIRE(factorial::computeFact(10) == 3628800);
}

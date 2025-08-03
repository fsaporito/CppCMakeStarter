#include "prime/prime.h"
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Primes are checked: 0", "[isPrime0]")
{
    REQUIRE(prime::isPrime(0) == false);
}

TEST_CASE("Primes are checked: 1", "[isPrime1]")
{
    REQUIRE(prime::isPrime(1) == false);
}

TEST_CASE("Primes are checked: 2", "[isPrime2]")
{
    REQUIRE(prime::isPrime(2) == true);
}

TEST_CASE("Primes are checked: 3", "[isPrime3]")
{
    REQUIRE(prime::isPrime(3) == true);
}

TEST_CASE("Primes are checked: 4", "[isPrime4]")
{
    REQUIRE(prime::isPrime(4) == false);
}

TEST_CASE("Primes are checked: 5", "[isPrime5]")
{
    REQUIRE(prime::isPrime(5) == true);
}

TEST_CASE("Primes are checked: 6", "[isPrime6]")
{
    REQUIRE(prime::isPrime(6) == false);
}

TEST_CASE("Primes are checked: 7", "[isPrime7]")
{
    REQUIRE(prime::isPrime(7) == true);
}

TEST_CASE("Primes are checked: 8", "[isPrime8]")
{
    REQUIRE(prime::isPrime(8) == false);
}

TEST_CASE("Primes are checked: 9", "[isPrime9]")
{
    REQUIRE(prime::isPrime(9) == false);
}

TEST_CASE("Primes are checked: 10", "[isPrime10]")
{
    REQUIRE(prime::isPrime(10) == false);
}

TEST_CASE("Primes are checked: 11", "[isPrime11]")
{
    REQUIRE(prime::isPrime(11) == true);
}

TEST_CASE("Primes are checked: 13", "[isPrime13]")
{
    REQUIRE(prime::isPrime(13) == true);
}

TEST_CASE("Primes are checked: 15", "[isPrime15]")
{
    REQUIRE(prime::isPrime(15) == false);
}

TEST_CASE("Primes are checked: 17", "[isPrime17]")
{
    REQUIRE(prime::isPrime(17) == true);
}

TEST_CASE("Primes are checked: 19", "[isPrime19]")
{
    REQUIRE(prime::isPrime(19) == true);
}

TEST_CASE("Primes are checked: 20", "[isPrime20]")
{
    REQUIRE(prime::isPrime(20) == false);
}

TEST_CASE("Primes are checked: 21", "[isPrime21]")
{
    REQUIRE(prime::isPrime(21) == false);
}

TEST_CASE("Primes are checked: 23", "[isPrime23]")
{
    REQUIRE(prime::isPrime(23) == true);
}

TEST_CASE("Primes are checked: 51", "[isPrime51]")
{
    REQUIRE(prime::isPrime(51) == false);
    BENCHMARK("isPrime 51")
    {
        return prime::isPrime(51);
    };
}

#include <catch2/catch.hpp>
#include "factorial/factorial.h"
#include "prime/prime.h"

TEST_CASE("Factorials are computed", "[computeFact]")
{
  REQUIRE(factorial::computeFact(0) == 1);
  REQUIRE(factorial::computeFact(1) == 1);
  REQUIRE(factorial::computeFact(2) == 2);
  REQUIRE(factorial::computeFact(3) == 6);
  REQUIRE(factorial::computeFact(4) == 24);
  REQUIRE(factorial::computeFact(5) == 120);
  REQUIRE(factorial::computeFact(6) == 720);
  REQUIRE(factorial::computeFact(7) == 5040);
  REQUIRE(factorial::computeFact(8) == 40320);
  REQUIRE(factorial::computeFact(9) == 362880);
  REQUIRE(factorial::computeFact(10) == 3628800);
}



TEST_CASE("Primes are checked", "[isPrime]")
{
  REQUIRE(!prime::isPrime(0));
  REQUIRE(prime::isPrime(1));
  REQUIRE(prime::isPrime(2));
  REQUIRE(prime::isPrime(3));
  REQUIRE(!prime::isPrime(4));
  REQUIRE(!prime::isPrime(5));
  REQUIRE(!prime::isPrime(6));
  REQUIRE(prime::isPrime(7));
  REQUIRE(!prime::isPrime(8));
  REQUIRE(!prime::isPrime(9));
  REQUIRE(!prime::isPrime(10));
  REQUIRE(prime::isPrime(11));
  REQUIRE(!prime::isPrime(12));
  REQUIRE(prime::isPrime(13));
  REQUIRE(!prime::isPrime(14));
  REQUIRE(!prime::isPrime(15));
  REQUIRE(!prime::isPrime(16));
  REQUIRE(prime::isPrime(17));
  REQUIRE(!prime::isPrime(18));
  REQUIRE(prime::isPrime(19));
}

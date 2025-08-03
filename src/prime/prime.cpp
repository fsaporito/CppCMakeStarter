#include "prime.h"
#include <cmath>

bool prime::isPrime(const int primeNumber)
{

    if (primeNumber <= 1)
        return false;

    if (primeNumber == 2 || primeNumber == 3)
        return true;

    if (primeNumber % 2 == 0)
        return false;

    auto primeNumberSqrt = static_cast<decltype(primeNumber)>(std::sqrt(primeNumber));

    for (int i = 3; i <= primeNumberSqrt; i += 2)
    {
        if (primeNumber % i == 0)
            return false;
    }

    return true;
}

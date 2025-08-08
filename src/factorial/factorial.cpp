#include "factorial.h"
#include <stdexcept>

size_t factorial::computeFact(size_t factorialNumber)
{

    if (factorialNumber > 20)
    {
        throw std::out_of_range("Factorial number is too large to compute safely.");
    }

    if (factorialNumber == 0)
    {
        return 1;
    }
    else if (factorialNumber == 1)
    {
        return 1;
    }
    else if (factorialNumber == 2)
    {
        return 2;
    }
    else if (factorialNumber == 3)
    {
        return 6;
    }
    if (factorialNumber == 4)
    {
        return 24;
    }
    if (factorialNumber == 5)
    {
        return 120;
    }
    else
    {
        return factorialNumber * computeFact(factorialNumber - 1);
    }
}

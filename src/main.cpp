#include <functional>
#include <iostream>
#include <optional>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>


#include "factorial/factorial.h"
#include "prime/prime.h"

int main(int argc, const char** argv)
{

    CLI::App app{"My App"};

    std::optional<size_t> factorialNumberInput = std::nullopt;
    app.add_option("--factorial", factorialNumberInput, "Factorial to Compute");

    std::optional<int> primeNumberInput = std::nullopt;
    app.add_option("--prime", primeNumberInput, "Check if number is prime");


    try
    {
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError& e)
    {
        return app.exit(e);
    }

    if (factorialNumberInput.has_value())
    {
        auto factorialNumberInputValue = factorialNumberInput.value();

        if (factorialNumberInputValue < 0)
        {
            spdlog::error("Cannot compute the factorial of a negative number {}", factorialNumberInputValue);
            return 1;
        }

        try
        {
            const auto fact = factorial::computeFact(factorialNumberInputValue);
            spdlog::info("Factorial of {} is: {}", factorialNumberInputValue, fact);
        } catch (const std::exception& e)
        {
            spdlog::error("Error computing factorial of {}: {}", factorialNumberInputValue, e.what());
            return 1;
        }

        return 0;
    }

    // Prime
    if (primeNumberInput.has_value())
    {
        auto       primeNumberInputValue = primeNumberInput.value();
        const auto is_prime              = prime::isPrime(primeNumberInputValue);

        spdlog::info("{} is {}", primeNumberInputValue, is_prime ? "Prime" : "Not Prime");

        return 0;
    }

    spdlog::error("No Option Given");

    return 1;
}

#include <crabpp/result.hpp>

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <iomanip>

using namespace crabpp;

enum class ErrorCode
{
    WRONG_VALUE
};

auto only_one__result(const int value) -> Result<int, ErrorCode>
{
    if (value != 1)
    {
        return Err<int, ErrorCode>(ErrorCode::WRONG_VALUE);
    }
    return Ok<int, ErrorCode>(1);
}


auto only_one__except(const int value) -> int
{
    if (value != 1)
    {
        throw std::runtime_error("WRONG VALUE");
    }
    return 1;
}

template <typename Func>
auto measure_execution_time(Func func) -> std::chrono::microseconds {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

int main()
{
    constexpr int testValue = 2;

    // Measure execution time using Result
    auto resultTime = measure_execution_time([&]() {
        auto result = only_one__result(testValue);
        if (!result) {
            std::cerr << "Result: WRONG VALUE\n";
        }
    });

    // Measure execution time using Exception
    auto exceptTime = measure_execution_time([&]() {
        try {
            auto result = only_one__except(testValue);
            std::cout << "Exception: " << result << '\n';
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << '\n';
        }
    });

    // Output execution times
    std::cout << "Result execution time: " << resultTime.count() << " microseconds\n";
    std::cout << "Exception execution time: " << exceptTime.count() << " microseconds\n";
}
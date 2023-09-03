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

auto only_one__result(std::string value) -> Result<std::string, ErrorCode>
{
    if (value != "dupa")
    {
        return Err<std::string, ErrorCode>(ErrorCode::WRONG_VALUE);
    }
    return Ok<std::string, ErrorCode>(std::move(value));
}


auto only_one__except(std::string value) -> int
{
    if (value != "dupa")
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
    std::string testValue = "dupak";

    auto exceptTime = measure_execution_time([&]() {
        try {
            auto result = only_one__except(testValue);
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    });
    
    auto resultTime = measure_execution_time([&]() {
        auto result = only_one__result(testValue);
        if (!result) {
            std::cerr << "Result: WRONG VALUE" << std::endl;
        }
    });


    std::cout << "Result execution time: " << resultTime.count() << " microseconds\n";
    std::cout << "Exception execution time: " << exceptTime.count() << " microseconds\n";
}
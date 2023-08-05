#include <crabpp/option.hpp>
#include <crabpp/result.hpp>

#include <iostream>

using namespace crabpp;

enum class ErrorCode
{
    WRONG_VALUE
};

auto only_one(const int& value) -> Result<int, ErrorCode>
{
    if (value != 1)
    {
        return Result<int, ErrorCode>(ErrorCode::WRONG_VALUE);
    }
    return Result<int, ErrorCode>(value);
}

int main()
{
    int i = 1;
    
    auto result = match<int, int>(i)
        .with(42, []() { return 100; })
        .with(10, []() { return 200; })
        .rest([]() { return 300; });

    std::cout << result << '\n';

    int value = 42;

    auto result2 = match<int, Option<int>>(value)
        .with(42, []() {return Some(10);})
        .with(99, []() {return Some(20);})
        .rest([]() -> Option<int> {return None();
        });

        std::cout << result2.unwrap() << '\n';

        auto result3 = only_one(1);

        std::cout << result3.unwrap() << '\n';

}
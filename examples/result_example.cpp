#include <CrabPP/result.hpp>

#include <iostream>
using namespace crabpp;

enum ErrorCode {
    SomeError
};

auto foo(int x) -> Result<std::string, ErrorCode> {
    if(x > 10)
    {
        return Err<std::string, ErrorCode>(ErrorCode::SomeError);
    }

    return Ok<std::string, ErrorCode>("The number is ok!");
}

void bar()
{
    auto result = foo(11);
    if(!result) {
    std::cerr << "Some error occured!";
    } else {
    std::cout << result.value();
    }
}
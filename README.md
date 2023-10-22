![Version](https://img.shields.io/badge/version-eternal_early_access-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-green.svg)

# CrabPP
It's an amateur library with useful systems from Rust lang.

## Usage

Before bulding make sure that you have C++17 compiler.
'''
git clone https://github.com/patrykstruzek/CrabPP
cd CrabPP
mkdir build
cd build
cmake ..
cmake --build .
'''

## Examples

### Result
'''cpp
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

auto result = foo(11);
if(!result) {
std::cerr << "Some error occured!";
} else {
std::cout << result.value();
}
'''

### match
'''cpp
std::string input = "some_text";

int result = match<std::string, int>(input)
                    .with("some_text", []() { return 0; })
                    .with("not_some_text", []() { return 1; })
                    .with("some_other_text", []() { return 2; })
                    .rest([]() { return NULL; });
'''

## Simple docs
- ### Result<T, E>
- .ok()
- .value()
- .unwrap()
- .expect()
- ### Ok<T, E>()
- ### Err<T, E>()
- ### match<T, R>()
- .with()
- .rest()

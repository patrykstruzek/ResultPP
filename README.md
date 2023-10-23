![Version](https://img.shields.io/badge/version-eternal_early_access-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-green.svg)

# CrabPP
It's an amateur library with useful systems from Rust lang.

## Usage

Before building make sure that you have C++17 compiler or higher.
```
git clone https://github.com/patrykstruzek/CrabPP
cd CrabPP
mkdir build
cd build
cmake ..
cmake --build .
```
then add to your CMakeLists.txt project
```
add_subdirectory(path_to_CrabPP)
target_link_libraries(your_target CrabPP::CrabPP)
```
or just add it through git submodule.

## Examples

### Result
```cpp
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
```

### match
```cpp
std::string input = "some_text";

int result = match<std::string, int>(input)
                    .with("some_text", []() { return 0; })
                    .with("not_some_text", []() { return 1; })
                    .with("some_other_text", []() { return 2; })
                    .rest([]() { return NULL; });
```

## Simple docs
- <strong>Result<T, E></strong> - main result class
- .err() - returns an error 
- .value() - returns a value
- .unwrap() - returns a value if ok, if not ok throw exception
- .expect() - if not ok throw exception with message in arguments
- <strong>Ok<T, E>()</strong> - returns an ok value
- <strong>Err<T, E>()</strong> - returns an error
- <strong>match<T, R>()</strong> - main match func
- .with() - compare with value from match arguments and return value
- .rest() - checks the rest cases and return a value

---
Take into account that this library has no real tests, so it is not perfect.

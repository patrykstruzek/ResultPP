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

```cpp
enum ErrorCode {
    SomeError
};

auto greater_than_nine(int x) -> Result<std::string_view, ErrorCode> {
    if(x <= 9)
        return Err(ErrorCode::SomeError);

    return Ok(std::string_view("The number is ok!"));
}

auto result = foo(11);

if(!result)
    std::cerr << "Some error occured!";
else
    std::cout << result.unwrap();
```

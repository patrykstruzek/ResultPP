![Version](https://img.shields.io/badge/version-eternal_early_access-blue.svg)
![Build Status](https://img.shields.io/badge/build-passing-green.svg)

# ResultPP
It's an amateur implementation of Result from Rust lang.

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

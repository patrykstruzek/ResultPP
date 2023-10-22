#include <CrabPP/matcher.hpp>
#include <string>

using namespace crabpp;

void matcher_example()
{
    std::string input = "some_text";

    int result = match<std::string, int>(input)
        .with("some_text", []() { return 0; })
        .with("not_some_text", []() { return 1; })
        .with("some_other_text", []() { return 2; })
        .rest([]() { return NULL; });
}
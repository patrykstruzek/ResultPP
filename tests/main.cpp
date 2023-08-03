#include <crabpp/option.hpp>

#include <iostream>

using namespace crabpp;

int main()
{
    int i = 1;

    match(i,
        {
        {1, []() { std::cout << "Yes" << std::endl; }},
        {2, []() { std::cout << "No" << std::endl; }}
    });
}
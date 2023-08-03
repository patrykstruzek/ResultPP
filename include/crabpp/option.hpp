#include <functional>
#include <optional>
#include <unordered_map>

namespace crabpp
{
// template <typename T>
// struct Option
// {
//     union Tag
//     {
//         std::optional<T> Some;
//         std::optional<T> None;

//         Tag() : None(std::nullopt) {}
//         Tag(T value) : Some(std::move(value)) {}
//         ~Tag() {}
//     };

//     Tag tag;

//     Option() : tag() {}
//     Option(T value) : tag(std::move(value)) {}
//     ~Option() {}
// };

    template<typename T>
    void match(const T& value, const std::unordered_map<T, std::function<void()>> variants)
    {
        auto it = variants.find(value);
        if (it != variants.end())
        {
            it->second();
        }
        else
        {
            std::cerr << "No matching variant found for value: " << value << std::endl;
        }
    }
}
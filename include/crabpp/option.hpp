#include <functional>
#include <unordered_map>
#include <stdexcept>

namespace crabpp
{

    // ---------- Option ----------

    template <typename T>
    class Option {
    private:
        bool hasValue;
        T value;

    public:
        Option() : hasValue(false), value(T()) {}

        Option(const T& val) : hasValue(true), value(val) {}

        ~Option() {
            if (hasValue) {
                value.~T();
            }
        }

        Option(const Option& other) : hasValue(other.hasValue) {
            if (hasValue) {
                new (&value) T(other.value);
            }
        }

        Option& operator=(const Option& other) {
            if (this != &other) {
                if (hasValue) {
                    value.~T();
                }
                hasValue = other.hasValue;
                if (hasValue) {
                    new (&value) T(other.value);
                }
            }
            return *this;
        }

        Option(Option&& other) : hasValue(other.hasValue) {
            if (hasValue) {
                new (&value) T(std::move(other.value));
                other.hasValue = false;
            }
        }

        Option& operator=(Option&& other) {
            if (this != &other) {
                if (hasValue) {
                    value.~T();
                }
                hasValue = other.hasValue;
                if (hasValue) {
                    new (&value) T(std::move(other.value));
                    other.hasValue = false;
                }
            }
            return *this;
        }

        bool is_some() const {
            return hasValue;
        }

        bool is_none() const {
            return !hasValue;
        }

        const T& unwrap() const {
            if (!hasValue) {
                throw std::logic_error("Option does not have a value");
            }
            return value;
        }
    };

    Option<int> Some(const int& val) {
        return Option<int>(val);
    }

    Option<int> None() {
        return Option<int>();
    }

    // ---------- match ----------

    template <typename T, typename R>
    class PatternMatcher {
    private:
        const T& value;
        bool matched;
        R result;

    public:
        PatternMatcher(const T& val) : value(val), matched(false) {}

        PatternMatcher& with(const T& pattern, const std::function<R()>& action) noexcept {
            if (!matched && value == pattern) {
                result = action();
                matched = true;
            }
            return *this;
        }

        R rest(const std::function<R()>& action) noexcept {
            if (!matched) {
                result = action();
                matched = true;
            }
            return result;
        }
    };

    template <typename T, typename R>
    PatternMatcher<T, R> match(const T& value) {
        return PatternMatcher<T, R>(value);
    }

}

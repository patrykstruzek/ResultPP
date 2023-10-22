#include <functional>

namespace crabpp {
template <typename T, typename R> class PatternMatcher {
private:
  const T& value;
  bool matched;
  R result;

public:
  PatternMatcher(const T& val) : value(val), matched(false) {}

  PatternMatcher &with(const T& pattern,
                       const std::function<R()>& action) noexcept {
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

template <typename T, typename R> PatternMatcher<T, R> match(const T& value) {
  return PatternMatcher<T, R>(value);
}

}

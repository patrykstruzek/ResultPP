#pragma once

#include <stdexcept>
#include <string>
#include <variant>

namespace crabpp {
struct None {};

template <typename T, typename E> class Result {
public:
  [[nodiscard]] const T& value() const noexcept {
    return std::get<T>(m_storage);
  }

  [[nodiscard]] const E& err() const noexcept { return std::get<E>(m_storage); }

  [[nodiscard]] const T& unwrap() const noexcept {
    if (std::holds_alternative<T>(m_storage)) {
      return std::get<T>(m_storage);
    } else {
      throw std::get<E>(m_storage);
    }
  }

  [[nodiscard]] const T& expect(const std::string& msg) const noexcept {
    if (std::holds_alternative<T>(m_storage)) {
      return std::get<T>(m_storage);
    } else {
      throw std::runtime_error(msg);
    }
  }

  explicit operator bool() const noexcept {
    return !std::holds_alternative<E>(m_storage);
  }

private:
  template <typename U, typename V> friend Result<U, V> Ok(U&& value) noexcept;

  template <typename U, typename V>
  friend Result<U, V> Ok(const U& value) noexcept;

  template <typename U, typename V> friend Result<U, V> Err(V error) noexcept;

  explicit Result(T&& value) : m_storage{std::move(value)} {}
  explicit Result(E&& error) : m_storage{std::move(error)} {}
  explicit Result(const T& value) : m_storage{value} {}

  std::variant<T, E> m_storage;
};

template <typename T, typename E>
[[nodiscard]] Result<T, E> Ok(T&& value) noexcept {
  return Result<T, E>{std::move(value)};
}

template <typename T, typename E>
[[nodiscard]] Result<T, E> Ok(const T& value) noexcept {
  return Result<T, E>{value};
}

template <typename T, typename E>
[[nodiscard]] Result<T, E> Err(E error) noexcept {
  return Result<T, E>{std::move(error)};
}
}
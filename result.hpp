#pragma once

#include <stdexcept>
#include <utility>
#include <variant>

namespace variants {
template <typename T>
struct [[nodiscard]] Ok {
    Ok(const T& val) : val(val) {}
    Ok(T&& val) : val(std::move(val)) {}

    T val;
};

template <>
struct Ok<void> {};

template <typename E>
struct [[nodiscard]] Err {
    Err(const E& err) : err(err) {}
    Err(E&& val) : err(std::move(val)) {}

    E err;
};
}

template <typename T, typename E>
class [[nodiscard]] Result {
  private:
    std::variant<variants::Ok<T>, variants::Err<E>> value;

  public:
    Result(variants::Ok<T> o) : value(std::move(o)) {}
    Result(variants::Err<E> e) : value(std::move(e)) {}

    [[nodiscard]] bool is_ok() const noexcept {
        return std::holds_alternative<variants::Ok<T>>(value);
    }

    [[nodiscard]] bool is_err() const noexcept { return !is_ok(); }

    [[nodiscard]] T unwrap() const {
        if (is_ok())
            return std::move(std::get<variants::Ok<T>>(value).val);
        else
            throw std::logic_error("Result contains an error (unwrap)");
    }

    template <typename F>
    [[nodiscard]] E expect(F&& msg) const {
        if (!is_ok())
            throw std::logic_error(
                std::forward<F>(msg)(std::get<variants::Err<E>>(value).err));
        else
            throw std::logic_error("Result does not contain an error (expect)");
    }

    [[nodiscard]] E err() const {
        if (is_err()) {
            return std::get<variants::Err<E>>(value).err;
        } else {
            throw std::logic_error(
                "Cannot call err() on a Result without an error");
        }
    }

    explicit operator bool() const noexcept { return is_ok(); }
};

template <typename T, typename CleanT = typename std::decay<T>::type>
[[nodiscard]] variants::Ok<CleanT> Ok(T&& val) {
    return variants::Ok<CleanT>(std::forward<T>(val));
}

inline variants::Ok<void> Ok() {
    return variants::Ok<void>();
}

template <typename E, typename CleanE = typename std::decay<E>::type>
[[nodiscard]] variants::Err<CleanE> Err(E&& val) {
    return variants::Err<CleanE>(std::forward<E>(val));
}
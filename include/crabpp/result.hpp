namespace crabpp
{

template <typename T, typename E>
struct Result
{
    union Value
    {
        T ok;
        E err;

        Value() {}
        ~Value() {}
    };

    enum class Tag
    {
        Ok,
        Err
    };

    Tag tag;
    Value value;

    Result(const T &data) : tag(Tag::Ok)
    {
        new (&value.ok) T(data);
    }

    Result(const E &error) : tag(Tag::Err)
    {
        new (&value.err) E(error);
    }

    ~Result()
    {
        if (tag == Tag::Ok)
            value.ok.~T();
        else
            value.err.~E();
    }

    Result(const Result &other) : tag(other.tag)
    {
        if (tag == Tag::Ok)
            new (&value.ok) T(other.value.ok);
        else
            new (&value.err) E(other.value.err);
    }

    Result &operator=(const Result &other)
    {
        if (this == &other)
            return *this;

        this->~Result();

        tag = other.tag;
        if (tag == Tag::Ok)
            new (&value.ok) T(other.value.ok);
        else
            new (&value.err) E(other.value.err);

        return *this;
    }

    Result(Result &&other) noexcept : tag(other.tag)
    {
        if (tag == Tag::Ok)
            new (&value.ok) T(std::move(other.value.ok));
        else
            new (&value.err) E(std::move(other.value.err));
    }

    Result &operator=(Result &&other) noexcept
    {
        if (this == &other)
            return *this;

        this->~Result();

        tag = other.tag;
        if (tag == Tag::Ok)
            new (&value.ok) T(std::move(other.value.ok));
        else
            new (&value.err) E(std::move(other.value.err));

        return *this;
    }

    bool is_ok() const { return tag == Tag::Ok; }
    bool is_err() const { return tag == Tag::Err; }

    explicit operator bool() const { return is_ok(); }

    const T& unwrap() const { return value.ok; }
    const E& unwrap_err() const { return value.err; } 
};

}

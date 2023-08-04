namespace crabpp
{
    template <typename OT, typename ET>
    struct Result
    {
        union Value
        {
            OT ok;
            ET err;

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

        Result(const OT &data) : tag(Tag::Ok)
        {
            new (&value.ok) OT(data);
        }

        Result(const ET &error) : tag(Tag::Err)
        {
            new (&value.err) ET(error);
        }

        ~Result()
        {
            if (tag == Tag::Ok)
                value.ok.~OT();
            else
                value.err.~ET();
        }

        Result(const Result &other) : tag(other.tag)
        {
            if (tag == Tag::Ok)
                new (&value.ok) OT(other.value.ok);
            else
                new (&value.err) ET(other.value.err);
        }

        Result &operator=(const Result &other)
        {
            if (this == &other)
                return *this;

            this->~Result();

            tag = other.tag;
            if (tag == Tag::Ok)
                new (&value.ok) OT(other.value.ok);
            else
                new (&value.err) ET(other.value.err);

            return *this;
        }

        Result(Result &&other) noexcept : tag(other.tag)
        {
            if (tag == Tag::Ok)
                new (&value.ok) OT(std::move(other.value.ok));
            else
                new (&value.err) ET(std::move(other.value.err));
        }

        Result &operator=(Result &&other) noexcept
        {
            if (this == &other)
                return *this;

            this->~Result();

            tag = other.tag;
            if (tag == Tag::Ok)
                new (&value.ok) OT(std::move(other.value.ok));
            else
                new (&value.err) ET(std::move(other.value.err));

            return *this;
        }

        const T& ok() const { return okValue; }
        const E& err() const { return errValue; }
    };
}   
#include <iostream>  // std::ostream
#include <stdexcept> // std::runtime_error

//-< interface >----------------------------------------------------------------

//-< basic level >- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class T>
class SmartPointer
{
public:
    using element_type = T;

    SmartPointer() = default;                                                                                   // task 1 (general)
    SmartPointer(element_type *data) : data_(data) {};                                                          // task 2: variant 1
    SmartPointer(SmartPointer const &other) : data_(other.data_ ? new element_type(*other.data_) : nullptr) {}; // task 2: variant 2
    SmartPointer(SmartPointer &&other) noexcept : data_(other.data_) { other.data_ = nullptr; };                // task 2: variant 3
    ~SmartPointer()                                                                                             // task 3 (general)
    {
        if (*this)
        {
            delete data_;
        }
    }

    auto data() -> element_type * { return data_; };             // task 4.1 (general)
    auto data() const -> element_type const * { return data_; }; // task 4.2 (general)

    operator bool() const { return data_ != nullptr; }; // task 5 (general)

    auto operator=(element_type *data) -> SmartPointer & // task 6: var. 3
    {
        if (data_ != data)
        {
            delete data_;
            data_ = data;
        }
        return *this;
    }; // task 6: var. 3
    auto operator=(SmartPointer const &other) -> SmartPointer &;     // task 6: var. 1
    auto operator=(SmartPointer &&other) noexcept -> SmartPointer &; // task 6: var. 2

private:
    element_type *data_ = nullptr;
};

template <class T>
auto operator<<(std::ostream &cout, SmartPointer<T> const &smartPointer) -> std::ostream & // task 7 (general)
{
    if (smartPointer)
    {
        std::cout << *smartPointer.data() << std::endl;
    }
    else
    {
        throw std::runtime_error("nullptr :(");
    }
    return cout;
}

template <class T>
SmartPointer<T> &SmartPointer<T>::operator=(SmartPointer<T> const &other)
{
    if (this != &other)
    {
        delete data_;
        data_ = other.data_ ? new element_type(*other.data_) : nullptr;
    }
    return *this;
}

template <class T>
SmartPointer<T> &SmartPointer<T>::operator=(SmartPointer &&other) noexcept
{
    if (this != &other)
    {
        delete data_;
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -< basic level >-

//-< advanced level >- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class T>
struct Data
{
    using element_type = T;

    element_type *data;

    operator bool() const { return data != nullptr; };
};

template <class T>
class SmartDataPointer : private Data<T>
{
public:
    using data_base = Data<T>;
    using typename data_base::element_type;
    using data_base::operator bool; // task 5 (general)

    SmartDataPointer() : data_base{nullptr} {};                                                                             // task 1 (general)
    SmartDataPointer(element_type *data) : data_base{data} {};                                                              // task 2: variant 1
    SmartDataPointer(SmartDataPointer const &other) : data_base{other.data_ ? new element_type(*other.data_) : nullptr} {}; // task 2: variant 2
    SmartDataPointer(SmartDataPointer &&other) noexcept : data_base{other.data_}                                            // task 2: variant 3
    {
        other.data = nullptr;
    };
    ~SmartDataPointer() // task 3 (general)
    {
        delete this->data;
    }

    auto data() -> element_type * { return data; }              // task 4.1 (general)
    auto data() const -> element_type const * { return data; }; // task 4.2 (general)

    auto operator=(element_type *data) -> SmartDataPointer & // t6: v3
    {
        if (this->data != data)
        {
            delete this->data;
            this->data = data;
        }
        return *this;
    }
    auto operator=(SmartDataPointer const &other) -> SmartDataPointer & // t6: v1
    {
        if (this != &other)
        {
            delete this->data;
            this->data = other.data_ ? new element_type(*other.data_) : nullptr;
        }
        return *this;
    }
    auto operator=(SmartDataPointer &&other) noexcept -> SmartDataPointer & // t6: v2i
    {
        if (this != &other)
        {
            delete this->data;
            this->data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -< advanced level >-

//----------------------------------------------------------------< interface >-

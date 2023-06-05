#include "Iterator.hpp"
// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// конструктор итератора
Iterator<T>::Iterator(Matrix<T> &matrix, const size_t index)
{
    this->_index = index;
    this->_data_iter = matrix._data;
    this->_rows = matrix._rows;
    this->_cols = matrix._cols;
}

template <MatrixType T>
// конструктор итератора
Iterator<T>::Iterator(const Matrix<T> &matrix, const size_t index)
{
    this->_index = index;
    this->_data_iter = matrix._data;
    this->_rows = matrix._rows;
    this->_cols = matrix._cols;
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// переопределили оператор присваивания =
Iterator<T>::iterator &Iterator<T>::operator=(const Iterator<T>::iterator &it)
{
    this->_data_iter = it._data;
    this->_index = it._index;
    this->_rows = it._rows;
    this->_cols = it._cols;

    return *this;
}

template <MatrixType T>
// переопределили оператор присваивания =
Iterator<T>::iterator &Iterator<T>::operator=(Iterator<T>::iterator &&it) noexcept
{
    this->_data_iter = it._data;
    this->_index = it._index;
    this->_rows = it._rows;
    this->_cols = it._cols;

    return *this;
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// переопределили !=
bool Iterator<T>::operator!=(Iterator<T>::iterator const &other) const
{
    return this->_index != other._index;
}

template <MatrixType T>
// переопределили ==
bool Iterator<T>::operator==(Iterator<T>::iterator const &other) const
{
    return this->_index == other._index;
}

template <MatrixType T>
// переопределили <
bool Iterator<T>::operator<(Iterator<T>::iterator const &other) const
{
    return this->_index < other._index;
}

template <MatrixType T>
// переопределили <=
bool Iterator<T>::operator<=(Iterator<T>::iterator const &other) const
{
    return this->_index <= other._index;
}

template <MatrixType T>
// переопределили >
bool Iterator<T>::operator>(Iterator<T>::iterator const &other) const
{
    return this->_index > other._index;
}

template <MatrixType T>
// переопределили >=
bool Iterator<T>::operator>=(Iterator<T>::iterator const &other) const
{
    return this->_index >= other._index;
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// переопределили префиксный инкремент
Iterator<T>::iterator &Iterator<T>::operator++()
{
    if (this->_index < this->_cols * this->_rows)
        ++_index;

    return *this;
}

template <MatrixType T>
// переопределили постфиксный инкремент
Iterator<T>::iterator Iterator<T>::operator++(int)
{
    iterator it(*this);

    ++(*this);

    return it;
}

template <MatrixType T>
// next
Iterator<T>::iterator &Iterator<T>::next()
{
    return operator++();
}

template <MatrixType T>
// переопределили префиксный декремент
Iterator<T>::iterator &Iterator<T>::operator--()
{
    if (this->_index > 0)
        --_index;

    return *this;
}

template <MatrixType T>
// переопределили постфиксный декремент
Iterator<T>::iterator Iterator<T>::operator--(int)
{
    iterator it(*this);

    --(*this);

    return it;
}

template <MatrixType T>
// переопределили оператор +
Iterator<T>::iterator Iterator<T>::operator+(const size_t value) const
{
    iterator it(*this);

    if (value < 0 && it._index < -value)
        it._index = 0;
    else
        it._index += value;

    if (it._index < 0)
        it._index = 0;
    else if (it._index > this->_rows * this->_cols)
        it._index = this->_rows * this->_cols;

    return it;
}

template <MatrixType T>
// переопределили оператор -
Iterator<T>::iterator Iterator<T>::operator-(const size_t value) const
{
    return operator+(-value);
}

template <MatrixType T>
// переопределили оператор +=
Iterator<T>::iterator &Iterator<T>::operator+=(const size_t value)
{
    if (value < 0 && this->_index < -value)
        this->_index = 0;
    else
        this->_index += value;

    if (this->_index < 0)
        this->_index = 0;
    else if (this->_index > this->_rows * this->_cols)
        this->_index = this->_rows * this->_cols;

    return *this;
}

template <MatrixType T>
// переопределили оператор -=
Iterator<T>::iterator &Iterator<T>::operator-=(const size_t value)
{
    return operator+=(-value);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// переопределили оператор разыменования *
T &Iterator<T>::operator*()
{
    this->_check_data("Итератор указывает на nullptr\n");
    this->_check_index("Итератор не находится в границах данных при выполнении оператора *");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[this->_index / this->_cols][this->_index % this->_cols];
}

template <MatrixType T>
// переопределили оператор разыменования *
const T &Iterator<T>::operator*() const
{
    this->_check_data("Итератор указывает на nullptr\n");
    this->_check_index("Итератор не находится в границах данных при выполнении const оператора *");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[this->_index / this->_cols][this->_index % this->_cols];
}

template <MatrixType T>
T &Iterator<T>::value()
{
    return operator*();
}

template <MatrixType T>
const T &Iterator<T>::value() const
{
    return operator*();
}

template <MatrixType T>
// переопределили ->
T *Iterator<T>::operator->()
{
    this->_check_data("Итератор указывает на nullptr\n");
    this->_check_index("Итератор не находится в границах данных при выполнении оператора ->");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[this->_index / this->_cols].get_address() + (this->_index % _cols);
}

template <MatrixType T>
// переопределили ->
const T *Iterator<T>::operator->() const
{
    this->_check_data("Итератор указывает на nullptr\n");
    this->_check_index("Итератор не находится в границах данных при выполнении const оператора ->");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[this->_index / this->_cols].get_address() + (this->_index % this->_cols);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// переопределили []
T &Iterator<T>::operator[](const size_t index)
{
    this->_check_data("Итератор указывает на nullptr\n");

    size_t tmp_index = this->_index;
    this->_index = index;

    this->_check_index("Итератор не находится в границах данных при выполнении оператора []");

    this->_index = tmp_index;

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[index / this->_cols][index % this->_cols];
}

template <MatrixType T>
// переопределили []
const T &Iterator<T>::operator[](const size_t index) const
{
    this->_check_data("Итератор указывает на nullptr\n");

    size_t tmp_index = this->_index;
    this->_index = index;

    this->_check_index("Итератор не находится в границах данных при выполнении const оператора []");

    this->_index = tmp_index;

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[index / this->_cols][index % this->_cols];
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
Iterator<T>::operator bool() const
{
    return this->_data_iter.expired();
}

template <MatrixType T>
bool Iterator<T>::is_end() const
{
    return this->_index == this->_rows * this->_cols;
}

template <MatrixType T>
bool Iterator<T>::is_valid_data() const
{
    return !this->_data_iter.expired();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <MatrixType T>
// метод для проверки индекса в итераторе
void Iterator<T>::_check_index(const string hint)
{
    if (this->_index < this->_rows * this->_cols)
        return;

    throw IteratorIndexError(__FILE__, typeid(*this).name(), __LINE__, hint);
}

template <MatrixType T>
// метод проверяет данные на валидность
void Iterator<T>::_check_data(const string hint) const
{
    if (is_valid_data())
        return;

    throw IteratorValidationError(__FILE__, typeid(*this).name(), __LINE__, hint);
}

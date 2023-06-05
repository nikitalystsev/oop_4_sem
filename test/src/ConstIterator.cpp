#include "ConstIterator.hpp"

// /////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// конструктор итератора
ConstIterator<T>::ConstIterator(Matrix<T> &matrix, const size_t index)
{
    _index = index;
    _data_iter = matrix._data;
    _rows = matrix._rows;
    _cols = matrix._cols;
}

template <typename T>
// конструктор итератора
ConstIterator<T>::ConstIterator(const Matrix<T> &matrix, const size_t index)
{
    _index = index;
    _data_iter = matrix._data;
    _rows = matrix._rows;
    _cols = matrix._cols;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор присваивания =
ConstIterator<T>::iterator &ConstIterator<T>::operator=(const ConstIterator<T>::iterator &it)
{
    this->_data_iter = it._data;
    this->_index = it._index;
    this->_rows = it._rows;
    this->_cols = it._cols;

    return *this;
}

template <typename T>
// переопределили оператор присваивания =
ConstIterator<T>::iterator &ConstIterator<T>::operator=(ConstIterator<T>::iterator &&it) noexcept
{
    this->_data_iter = it._data;
    this->_index = it._index;
    this->_rows = it._rows;
    this->_cols = it._cols;

    return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили !=
bool ConstIterator<T>::operator!=(ConstIterator<T>::iterator const &other) const
{
    return this->_index != other._index;
}

template <typename T>
// переопределили ==
bool ConstIterator<T>::operator==(ConstIterator<T>::iterator const &other) const
{
    return this->_index == other._index;
}

template <typename T>
// переопределили <
bool ConstIterator<T>::operator<(ConstIterator<T>::iterator const &other) const
{
    return this->_index < other._index;
}

template <typename T>
// переопределили <=
bool ConstIterator<T>::operator<=(ConstIterator<T>::iterator const &other) const
{
    return this->_index <= other._index;
}

template <typename T>
// переопределили >
bool ConstIterator<T>::operator>(ConstIterator<T>::iterator const &other) const
{
    return this->_index > other._index;
}

template <typename T>
// переопределили >=
bool ConstIterator<T>::operator>=(ConstIterator<T>::iterator const &other) const
{
    return this->_index >= other._index;
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили префиксный инкремент
ConstIterator<T>::iterator &ConstIterator<T>::operator++() const
{
    if (this->_index < this->_cols * this->_rows)
        ++_index;

    return *this;
}

template <typename T>
// переопределили постфиксный инкремент
ConstIterator<T>::iterator ConstIterator<T>::operator++(int) const
{
    iterator it(*this);

    ++(*this);

    return it;
}

template <typename T>
// next
ConstIterator<T>::iterator &ConstIterator<T>::next() const
{
    return operator++();
}

template <typename T>
ConstIterator<T>::iterator &ConstIterator<T>::operator--() const
{
    if (_index > 0)
        --_index;

    return *this;
}

template <typename T>
ConstIterator<T>::iterator ConstIterator<T>::operator--(int) const
{
    iterator it(*this);

    --(*this);

    return it;
}

template <typename T>
// переопределили оператор +
ConstIterator<T>::iterator ConstIterator<T>::operator+(const size_t value) const
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

template <typename T>
// переопределили оператор -
ConstIterator<T>::iterator ConstIterator<T>::operator-(const size_t value) const
{
    return operator+(-value);
}

template <typename T>
// переопределили оператор +=
ConstIterator<T>::iterator &ConstIterator<T>::operator+=(const size_t value) const
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

template <typename T>
// переопределили оператор -=
ConstIterator<T>::iterator &ConstIterator<T>::operator-=(const size_t value) const
{
    return operator+=(-value);
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор разыменования *
const T &ConstIterator<T>::operator*() const
{
    this->_check_data("Const Итератор указывает на nullptr\n");
    this->_check_index("Const Итератор не находится в границах данных при выполнении const оператора *");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[this->_index / this->_cols][this->_index % this->_cols];
}

template <typename T>
const T &ConstIterator<T>::value() const
{
    return operator*();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили ->
const T *ConstIterator<T>::operator->() const
{
    this->_check_data("Const Итератор указывает на nullptr\n");
    this->_check_index("Const Итератор не находится в границах данных при выполнении const оператора ->");

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[_index / _cols].get_address() + (_index % _cols);
}

template <typename T>
// переопределили []
const T &ConstIterator<T>::operator[](const size_t index) const
{
    this->_check_data("Const Итератор указывает на nullptr\n");

    size_t tmp_index = this->_index;
    this->_index = index;

    this->_check_index("Const Итератор не находится в границах данных при выполнении const оператора []");

    this->_index = tmp_index;

    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = this->_data_iter.lock();

    return data_ptr[index / this->_cols][index % this->_cols];
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ConstIterator<T>::operator bool() const
{
    return this->_data_iter.expired();
}

template <typename T>
bool ConstIterator<T>::is_end() const
{
    return this->_index == this->_rows * this->_cols;
}

template <typename T>
bool ConstIterator<T>::is_valid_data() const
{
    return !this->_data_iter.expired();
}

// ///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// метод для проверки индекса в итераторе
void ConstIterator<T>::_check_index(const string hint)
{
    if (this->_index < this->_rows * this->_cols)
        return;

    throw IteratorIndexError(__FILE__, typeid(*this).name(), __LINE__, hint);
}

template <typename T>
// метод проверяет данные на валидность
void ConstIterator<T>::_check_data(const string hint) const
{
    if (is_valid_data())
        return;

    throw IteratorValidationError(__FILE__, typeid(*this).name(), __LINE__, hint);
}
#ifndef __CONSTITERATOR_HPP__
#define __CONSTITERATOR_HPP__

#include <iostream>
#include <memory>

#include "Matrix.hpp"

using string = std::string;

template <typename T> // объявление класса Matrix
class Matrix;

template <typename T>
class ConstIterator
{
public:
    // определили алиасы типов
    using iterator_type = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;

    ConstIterator(const Matrix<T> &matrix, const size_t index = 0); // конструктор итератора
    ConstIterator(const ConstIterator<T> &it) = default;            // конструктор копирования
    ConstIterator(ConstIterator &&it) noexcept = default;           // конструктор перемещения

    ~ConstIterator() noexcept = default; // деструктор дефолтный

    // сравнение
    bool operator!=(ConstIterator<T> const &other) const;
    bool operator==(ConstIterator<T> const &other) const;
    bool operator<(ConstIterator<T> const &other) const;
    bool operator<=(ConstIterator<T> const &other) const;
    bool operator>(ConstIterator<T> const &other) const;
    bool operator>=(ConstIterator<T> const &other) const;

    // перемещение
    ConstIterator<T> &operator++() const;
    ConstIterator<T> operator++(int) const;
    ConstIterator<T> &next() const;
    ConstIterator<T> &operator--() const;
    ConstIterator<T> operator--(int) const;
    ConstIterator<T> operator+(const int value) const;
    ConstIterator<T> operator-(const int value) const;
    ConstIterator<T> &operator+=(const int value) const;
    ConstIterator<T> &operator-=(const int value) const;

    // доступ
    const T &operator*() const;
    const T *operator->() const;
    const T &operator[](const size_t index) const;

    operator bool() const;
    bool is_end() const;
    bool is_valid_data() const;

private:
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> _data_iter;
    mutable size_t _index = 0; // индекс это номер элемента в матрице ка если бы все ее элементы построчно расположились бы на одной строки
    size_t _rows = 0;
    size_t _cols = 0;

    void _check_index(const string hint = "");
    void _check_data(const string hint = "") const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// конструктор итератора
ConstIterator<T>::ConstIterator(const Matrix<T> &matrix, const size_t index)
{
    _index = index;
    _data_iter = matrix._data;
    _rows = matrix._rows;
    _cols = matrix._cols;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили !=
bool ConstIterator<T>::operator!=(ConstIterator<T> const &other) const
{
    return _index != other._index;
}

template <typename T>
// переопределили ==
bool ConstIterator<T>::operator==(ConstIterator<T> const &other) const
{
    return _index == other._index;
}

template <typename T>
// переопределили <
bool ConstIterator<T>::operator<(ConstIterator<T> const &other) const
{
    return _index < other._index;
}

template <typename T>
// переопределили <=
bool ConstIterator<T>::operator<=(ConstIterator<T> const &other) const
{
    return _index <= other._index;
}

template <typename T>
// переопределили >
bool ConstIterator<T>::operator>(ConstIterator<T> const &other) const
{
    return _index > other._index;
}

template <typename T>
// переопределили >=
bool ConstIterator<T>::operator>=(ConstIterator<T> const &other) const
{
    return _index < other._index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили префиксный инкремент
ConstIterator<T> &ConstIterator<T>::operator++() const
{
    if (_index < _cols * _rows)
        ++_index;

    return *this;
}

template <typename T>
// переопределили постфиксный инкремент
ConstIterator<T> ConstIterator<T>::operator++(int) const
{
    ConstIterator<T> it(*this);

    ++(*this);

    return it;
}

template <typename T>
// next
ConstIterator<T> &ConstIterator<T>::next() const
{
    return operator++();
}

template <typename T>
ConstIterator<T> &ConstIterator<T>::operator--() const
{
    if (_index < _cols * _rows)
    {
        --_index;
    }

    return *this;
}

template <typename T>
ConstIterator<T> ConstIterator<T>::operator--(int) const
{
    ConstIterator<T> iter(*this);

    --(*this);

    return iter;
}

template <typename T>
// переопределили оператор +
ConstIterator<T> ConstIterator<T>::operator+(const int value) const
{
    ConstIterator<T> it(*this);

    if (value < 0 && it._index < static_cast<size_t>(-value))
        it._index = 0;
    else
        it._index += value;

    if (it._index < 0)
        it._index = 0;
    else if (it._index > _rows * _cols)
        it._index = _rows * _cols;

    return it;
}

template <typename T>
// переопределили оператор -
ConstIterator<T> ConstIterator<T>::operator-(const int value) const
{
    return operator+(-value);
}

template <typename T>
// переопределили оператор +=
ConstIterator<T> &ConstIterator<T>::operator+=(const int value) const
{
    _index += value;

    return *this;
}

template <typename T>
// переопределили оператор -=
ConstIterator<T> &ConstIterator<T>::operator-=(const int value) const
{
    _index -= value;

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор разыменования *
const T &ConstIterator<T>::operator*() const
{
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили ->
const T *ConstIterator<T>::operator->() const
{
    std::shared_ptr<typename Matrix<T>::MatrixRow[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols].get_address() + (_index % _cols);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ConstIterator<T>::operator bool() const
{
    return _data_iter.expired();
}

template <typename T>
bool ConstIterator<T>::is_end() const
{
    return _index == _rows * _cols;
}

template <typename T>
bool ConstIterator<T>::is_valid_data() const
{
    return !_data_iter.expired();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// метод для проверки индекса в итераторе
void ConstIterator<T>::_check_index(const string hint)
{
    if (_index < _rows * _cols)
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

#endif // __CONSTITERATOR_HPP__
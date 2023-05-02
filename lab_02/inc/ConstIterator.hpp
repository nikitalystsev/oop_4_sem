#ifndef __CONSTITERATOR_HPP__
#define __CONSTITERATOR_HPP__

#include <iostream>
#include <memory>

#include "Matrix.hpp"

template <typename T> // объявление класса Matrix
class Matrix;

template <typename T>
class ConstIterator
{
public:
    // определили алиасы типов
    using iterator_type = std::random_access_iterator_tag;
    using value_type = T;
    using pointer_type = T *;
    using l_link_type = T &;

    explicit ConstIterator() = default;                             // конструктор без параметров по умолчанию
    ConstIterator(const Matrix<T> &matrix, const size_t index = 0); // конструктор итератора
    explicit ConstIterator(const ConstIterator<T> &it) = default;        // конструктор копирования

    ~ConstIterator() noexcept = default; // деструктор дефолтный

    bool operator!=(ConstIterator const &other) const;
    bool operator==(ConstIterator const &other) const;
    bool operator<(ConstIterator const &other) const;

    ConstIterator<T> operator+(const int value) const;
    ConstIterator<T> operator-(const int value) const;
    ConstIterator<T> &operator+=(const int value) const;
    ConstIterator<T> &operator-=(const int value) const;

    ConstIterator<T> &operator++() const;
    ConstIterator<T> operator++(int) const;
    ConstIterator<T> &next() const;

    const T &operator*() const;
    const T *operator->() const;

    operator bool() const;
    bool is_end() const;
    bool is_valid_data() const;

private:
    std::weak_ptr<MatrixRow<T>[]> _data_iter;
    mutable size_t _index = 0; // индекс это номер элемента в матрице ка если бы все ее элементы построчно расположились бы на одной строки
    size_t _rows = 0;
    size_t _cols = 0;
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
bool ConstIterator<T>::operator!=(ConstIterator const &other) const
{
    return _index != other._index;
}

template <typename T>
// переопределили ==
bool ConstIterator<T>::operator==(ConstIterator const &other) const
{
    return _index == other._index;
}

template <typename T>
// переопределили <
bool ConstIterator<T>::operator<(ConstIterator const &other) const
{
    return _index < other._index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

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
    Iterator<T> it(*this);

    ++(*this);

    return it;
}

template <typename T>
// next
ConstIterator<T> &ConstIterator<T>::next() const
{
    return operator++();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор разыменования *
const T &ConstIterator<T>::operator*() const
{
    std::shared_ptr<MatrixRow<T>[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили ->
const T *ConstIterator<T>::operator->() const
{
    std::shared_ptr<MatrixRow<T>[]> data_ptr = _data_iter.lock();

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

#endif // __CONSTITERATOR_HPP__
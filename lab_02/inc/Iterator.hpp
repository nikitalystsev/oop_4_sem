#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <memory>

#include "Matrix.hpp"

template <typename T> // объявление класса Matrix
class Matrix;

template <typename T>
class Iterator
{
public:
    // определили алиасы типов
    using iterator_type = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;

    Iterator(const Matrix<T> &matrix, const size_t index = 0); // конструктор итератора
    Iterator(const Iterator<T> &it) = default;                 // конструктор копирования
    Iterator(Iterator &&it) noexcept = default;                // конструктор перемещения
    
    ~Iterator() noexcept = default;                            // деструктор дефолтный

    bool operator!=(Iterator const &other) const;
    bool operator==(Iterator const &other) const;
    bool operator<(Iterator const &other) const;

    Iterator<T> operator+(const int value) const;
    Iterator<T> operator-(const int value) const;
    Iterator<T> &operator+=(const int value);
    Iterator<T> &operator-=(const int value);

    Iterator<T> &operator=(const Iterator<T> &it);

    Iterator<T> &operator++();
    Iterator<T> operator++(int);
    Iterator<T> &next();

    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;

    operator bool() const;
    bool is_end() const;
    bool is_valid_data() const;

private:
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> _data_iter;
    size_t _index = 0; // индекс это номер элемента в матрице ка если бы все ее элементы построчно расположились бы на одной строки
    size_t _rows = 0;
    size_t _cols = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// конструктор итератора
Iterator<T>::Iterator(const Matrix<T> &matrix, const size_t index)
{
    _index = index;
    _data_iter = matrix._data;
    _rows = matrix._rows;
    _cols = matrix._cols;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили !=
bool Iterator<T>::operator!=(Iterator const &other) const
{
    return _index != other._index;
}

template <typename T>
// переопределили ==
bool Iterator<T>::operator==(Iterator const &other) const
{
    return _index == other._index;
}

template <typename T>
// переопределили <
bool Iterator<T>::operator<(Iterator const &other) const
{
    return _index < other._index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор +
Iterator<T> Iterator<T>::operator+(const int value) const
{
    Iterator<T> it(*this);

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
Iterator<T> Iterator<T>::operator-(const int value) const
{
    return operator+(-value);
}

template <typename T>
// переопределили оператор +=
Iterator<T> &Iterator<T>::operator+=(const int value)
{
    _index += value;

    return *this;
}

template <typename T>
// переопределили оператор -=
Iterator<T> &Iterator<T>::operator-=(const int value)
{
    _index -= value;

    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор присваивания =
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &it)
{
    _data_iter = it._data;
    _index = it._index;
    _rows = it._rows;
    _cols = it._cols;

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили префиксный инкремент
Iterator<T> &Iterator<T>::operator++()
{
    if (_index < _cols * _rows)
        ++_index;

    return *this;
}

template <typename T>
// переопределили постфиксный инкремент
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> it(*this);

    ++(*this);

    return it;
}

template <typename T>
// next
Iterator<T> &Iterator<T>::next()
{
    return operator++();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили оператор разыменования *
T &Iterator<T>::operator*()
{
    // позже добавить проверки на валидность указателя  и правильность индекса

    std::shared_ptr<typename Matrix<T>::MatrixRow<T>[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

template <typename T>
// переопределили оператор разыменования *
const T &Iterator<T>::operator*() const
{
    std::shared_ptr<typename Matrix<T>::MatrixRow<T>[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переопределили ->
T *Iterator<T>::operator->()
{
    std::shared_ptr<typename Matrix<T>::MatrixRow<T>[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols].get_address() + (_index % _cols);
}

template <typename T>
// переопределили ->
const T *Iterator<T>::operator->() const
{
    std::shared_ptr<typename Matrix<T>::MatrixRow<T>[]> data_ptr = _data_iter.lock();

    return data_ptr[_index / _cols].get_address() + (_index % _cols);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Iterator<T>::operator bool() const
{
    return _data_iter.expired();
}

template <typename T>
bool Iterator<T>::is_end() const
{
    return _index == _rows * _cols;
}

template <typename T>
bool Iterator<T>::is_valid_data() const
{
    return !_data_iter.expired();
}

#endif // __ITERATOR_HPP__
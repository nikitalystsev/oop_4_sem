#pragma once

#include <memory>
#include <string>

#include "exception.hpp"

template<typename T>
using SharedPtr = std::shared_ptr<T>;
template<typename T>
using WeakPtr = std::weak_ptr<T>;

template<typename T>
class Matrix;

template<typename T>
class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    // конструктор класса
    ConstIterator(const Matrix<T> &matrix, const size_t index = 0) :
            _data(matrix._data), _index(index),
            _rows(matrix._rows), _cols(matrix._cols) {}

    // конструктор копирования
    ConstIterator(const ConstIterator &it) = default;

    bool operator!=(ConstIterator const &other) const;

    bool operator==(ConstIterator const &other) const;

    bool operator<(ConstIterator const &other) const;

    operator bool() const;

    ConstIterator<T> operator+(const int value) const;

    ConstIterator<T> operator-(const int value) const;

    ConstIterator<T> &operator+=(const int value) const;

    const ConstIterator<T> &operator++() const;

    ConstIterator<T> operator++(int) const;

    const T &operator*() const;

    const T *operator->() const;

    const T &value() const;

    ConstIterator<T> &next() const;

    bool is_end() const;

    bool is_valid() const;

private:
    void _check_index(const string hint = "") const;

    void _check_valid(const string hint = "") const;

    WeakPtr<typename Matrix<T>::MatrixRow[]> _data = nullptr;
    mutable size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

/* реализация */

template<typename T>
// переопределили (перегрузили) !=
bool ConstIterator<T>::operator!=(ConstIterator const &other) const {

    return _index != other._index;
}

template<typename T>
// переопределили ==
bool ConstIterator<T>::operator==(ConstIterator const &other) const {

    return _index == other._index;
}

template<typename T>
// переопределили оператор <
bool ConstIterator<T>::operator<(ConstIterator const &other) const {

    return _index < other._index;
}

template<typename T>
// переопределили оператор bool
ConstIterator<T>::operator bool() const {

    return _data.expired();
}

template<typename T>
// переопределили +
ConstIterator<T> ConstIterator<T>::operator+(const int value) const {
    ConstIterator<T> it(*this);

    if (value < 0 && it._index < static_cast<size_t>(-value))
        it._index = 0;
    else
        it._index += value;

    if (it._index > _rows * _cols)
        it._index = _rows * _cols;

    return it;
}

template<typename T>
// переопределили -
ConstIterator<T> ConstIterator<T>::operator-(const int value) const {

    return operator+(-value);
}

template<typename T>
// переопределили -=
ConstIterator<T> &ConstIterator<T>::operator+=(const int value) const {
    _index += value;

    return *this;
}

template<typename T>
// переопределили префиксный инкремент
const ConstIterator<T> &ConstIterator<T>::operator++() const {
    if (_index < _cols * _rows)
        ++_index;

    return *this;
}

template<typename T>
// переопределили постфиксный инкремент
ConstIterator<T> ConstIterator<T>::operator++(int) const {
    ConstIterator<T> it(*this);

    ++(*this);

    return it;
}

template<typename T>
// переопределили * (оператор разыменования)
const T &ConstIterator<T>::operator*() const {
    _check_valid("Iterator points on nullptr");
    _check_index("ConstIterator doesn't in data bounds, while executing const operator*");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

template<typename T>
// переопределили оператор  ->
const T *ConstIterator<T>::operator->() const {
    _check_valid("Iterator points on nullptr");
    _check_index("ConstIterator doesn't in data bounds, while executing const operator->");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template<typename T>
const T &ConstIterator<T>::value() const {

    return operator*();
}

template<typename T>
ConstIterator<T> &ConstIterator<T>::next() const {

    return operator++();
}

template<typename T>
void ConstIterator<T>::_check_index(const string hint) const {
    if (_index < _rows * _cols)
        return;

    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);
    throw IteratorIndexError(
            asctime(local_time),
            __FILE__,
            typeid(*this).name(),
            __LINE__, hint);
}

template<typename T>
void ConstIterator<T>::_check_valid(const string hint) const {
    if (is_valid())
        return;

    time_t cur_time = time(NULL);
    auto local_time = localtime(&cur_time);
    throw IteratorValidationError(
            asctime(local_time),
            __FILE__,
            typeid(*this).name(),
            __LINE__, hint);
}

template<typename T>
bool ConstIterator<T>::is_end() const {

    return _index == _rows * _cols;
}

template<typename T>
bool ConstIterator<T>::is_valid() const {

    return !_data.expired();
}

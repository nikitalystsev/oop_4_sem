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
class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    Iterator(const Matrix<T> &matrix, const size_t index = 0) :
            _data(matrix._data), _index(index),
            _rows(matrix._rows), _cols(matrix._cols) {}

    Iterator(const Iterator &it) = default;

    bool operator!=(Iterator const &other) const;

    bool operator==(Iterator const &other) const;

    bool operator<(Iterator const &other) const;

    operator bool() const;

    Iterator<T> operator+(const int value) const;

    Iterator<T> operator-(const int value) const;

    Iterator<T> &operator+=(const int value);

    Iterator<T> &operator=(const Iterator<T> &it);

    Iterator<T> &operator++();

    Iterator<T> operator++(int);

    T &operator*();

    const T &operator*() const;

    T *operator->();

    const T *operator->() const;

    T &value();

    const T &value() const;

    Iterator<T> &next();

    bool is_end() const;

    bool is_valid() const;

private:
    void _check_index(const string hint = "");

    void _check_valid(const string hint = "") const;

    WeakPtr<typename Matrix<T>::MatrixRow[]> _data;
    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};

/* реализация */

template<typename T>
// переопределили !=
bool Iterator<T>::operator!=(Iterator const &other) const {

    return _index != other._index;
}

template<typename T>
// переопределили ==
bool Iterator<T>::operator==(Iterator const &other) const {

    return _index == other._index;
}

template<typename T>
// переопределили <
bool Iterator<T>::operator<(Iterator const &other) const {

    return _index < other._index;
}

template<typename T>
// переопределили оператор bool
Iterator<T>::operator bool() const {

    return _data.expired();
}

template<typename T>
// переопределили оператор +
Iterator<T> Iterator<T>::operator+(const int value) const {
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

template<typename T>
// переопределили оператор -
Iterator<T> Iterator<T>::operator-(const int value) const {

    return operator+(-value);
}

template<typename T>
// переопределили оператор +=
Iterator<T> &Iterator<T>::operator+=(const int value) {
    _index += value;

    return *this;
}

template<typename T>
// переопределили оператор присваивания =
Iterator<T> &Iterator<T>::operator=(const Iterator<T> &it) {
    _data = it._data;
    _index = it._index;
    _rows = it._rows;
    _cols = it._cols;

    return *this;
}

template<typename T>
// переопределили префиксный инкремент
Iterator<T> &Iterator<T>::operator++() {
    if (_index < _cols * _rows)
        ++_index;

    return *this;
}

template<typename T>
// переопределили постфиксный инкремент
Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> it(*this);

    ++(*this);

    return it;
}

template<typename T>
// переопределили оператор разыменования *
T &Iterator<T>::operator*() {
    _check_valid("Iterator points on nullptr");
    _check_index("Iterator doesn't in data bounds, while executing operator*");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

template<typename T>
// переопределили оператор разыменования *
const T &Iterator<T>::operator*() const {
    _check_valid("Iterator points on nullptr");
    _check_index("Iterator doesn't in data bounds, while executing const operator*");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols][_index % _cols];
}

template<typename T>
// переопределили ->
T *Iterator<T>::operator->() {
    _check_valid("Iterator points on nullptr");
    _check_index("Iterator doesn't in data bounds, while executing operator->");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template<typename T>
// переопределили ->
const T *Iterator<T>::operator->() const {
    _check_valid("Iterator points on nullptr");
    _check_index("Iterator doesn't in data bounds, while executing const operator->");

    SharedPtr<typename Matrix<T>::MatrixRow[]> data_ptr = _data.lock();

    return data_ptr[_index / _cols].getAddr() + (_index % _cols);
}

template<typename T>
T &Iterator<T>::value() {

    return operator*();
}

template<typename T>
const T &Iterator<T>::value() const {

    return operator*();
}

template<typename T>
Iterator<T> &Iterator<T>::next() {

    return operator++();
}

template<typename T>
bool Iterator<T>::is_end() const {

    return _index == _rows * _cols;
}

template<typename T>
bool Iterator<T>::is_valid() const {

    return !_data.expired();
}

template<typename T>
void Iterator<T>::_check_index(const string hint) {
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
void Iterator<T>::_check_valid(const string hint) const {
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


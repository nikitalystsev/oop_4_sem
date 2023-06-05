#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <memory>

#include "Matrix.hpp"
#include "MatrixExceptions.hpp"

using string = std::string;

template <typename T> // объявление класса Matrix
class Matrix;

template <typename T>
class Iterator
{
public:
    // определили алиасы типов
    using iterator_type = std::random_access_iterator_tag; // итератор произвольного доступа
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;

    Iterator(const Matrix<T> &matrix, const size_t index = 0); // конструктор итератора
    Iterator(const Iterator<T> &it) = default;                 // конструктор копирования
    Iterator(Iterator &&it) noexcept = default;                // конструктор перемещения

    ~Iterator() noexcept = default; // деструктор дефолтный

    // оператор присваивания
    Iterator<T> &operator=(const Iterator<T> &it);

    // сравнение
    bool operator!=(Iterator<T> const &other) const;
    bool operator==(Iterator<T> const &other) const;
    bool operator<(Iterator<T> const &other) const;
    bool operator<=(Iterator<T> const &other) const;
    bool operator>(Iterator<T> const &other) const;
    bool operator>=(Iterator<T> const &other) const;

    // перемещение
    Iterator<T> &operator++();
    Iterator<T> operator++(int);
    Iterator<T> &next();
    Iterator<T> &operator--();
    Iterator<T> operator--(int);
    Iterator<T> operator+(const int value) const;
    Iterator<T> operator-(const int value) const;
    Iterator<T> &operator+=(const int value);
    Iterator<T> &operator-=(const int value);

    // доступitera
    T &operator*();
    const T &operator*() const;
    T *operator->();
    const T *operator->() const;
    T &operator[](const size_t index);
    const T &operator[](const size_t index) const;

    operator bool() const;
    bool is_end() const;
    bool is_valid_data() const;

private:
    std::weak_ptr<typename Matrix<T>::MatrixRow[]> _data_iter;
    size_t _index = 0; // индекс это номер элемента в матрице ка если бы все ее элементы построчно расположились бы на одной строки
    size_t _rows = 0;
    size_t _cols = 0;

    // приватные матоды
    void _check_index(const string hint = "");
    void _check_data(const string hint = "") const;
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

#endif // __ITERATOR_HPP__

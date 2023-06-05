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

    // // сравнение
    // bool operator!=(ConstIterator<T> const &other) const;
    // bool operator==(ConstIterator<T> const &other) const;
    // bool operator<(ConstIterator<T> const &other) const;
    // bool operator<=(ConstIterator<T> const &other) const;
    // bool operator>(ConstIterator<T> const &other) const;
    // bool operator>=(ConstIterator<T> const &other) const;

    // // перемещение
    // ConstIterator<T> &operator++() const;
    // ConstIterator<T> operator++(int) const;
    // ConstIterator<T> &next() const;
    // ConstIterator<T> &operator--() const;
    // ConstIterator<T> operator--(int) const;
    // ConstIterator<T> operator+(const int value) const;
    // ConstIterator<T> operator-(const int value) const;
    // ConstIterator<T> &operator+=(const int value) const;
    // ConstIterator<T> &operator-=(const int value) const;

    // // доступ
    // const T &operator*() const;
    // const T *operator->() const;
    // const T &operator[](const size_t index) const;

    // operator bool() const;
    // bool is_end() const;
    // bool is_valid_data() const;

private:
    // std::weak_ptr<typename Matrix<T>::MatrixRow[]> _data_iter;
    mutable size_t _index = 0; // индекс это номер элемента в матрице ка если бы все ее элементы построчно расположились бы на одной строки
    size_t _rows = 0;
    size_t _cols = 0;

    // void _check_index(const string hint = "");
    // void _check_data(const string hint = "") const;
};


#endif // __CONSTITERATOR_HPP__
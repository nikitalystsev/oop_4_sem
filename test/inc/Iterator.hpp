#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <iostream>
#include <memory>

#include "Concepts.hpp"
#include "MatrixExceptions.hpp"

using string = std::string;

template <MatrixType T> // объявление класса Matrix
class Matrix;

template <MatrixType T>
class Iterator
{
public:
    // определили алиасы типов
    using iterator_type = std::random_access_iterator_tag; // итератор произвольного доступа
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_const_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator = Iterator<T>;

    Iterator(Matrix<T> &matrix, const size_t index = 0);       // конструктор итератора
    Iterator(const Matrix<T> &matrix, const size_t index = 0); // конструктор итератора
    Iterator(const Iterator &it) = default;                    // конструктор копирования
    Iterator(Iterator &&it) noexcept = default;                // конструктор перемещения

    ~Iterator() noexcept = default; // деструктор дефолтный

    // оператор присваивания
    iterator &operator=(const iterator &it);
    iterator &operator=(iterator &&it) noexcept;

    // сравнение
    bool operator!=(iterator const &other) const;
    bool operator==(iterator const &other) const;
    bool operator<(iterator const &other) const;
    bool operator<=(iterator const &other) const;
    bool operator>(iterator const &other) const;
    bool operator>=(iterator const &other) const;

    // перемещение
    iterator &operator++();
    iterator operator++(int);
    iterator &next();
    iterator &operator--();
    iterator operator--(int);
    iterator operator+(const size_t value) const;
    iterator operator-(const size_t value) const;
    iterator &operator+=(const size_t value);
    iterator &operator-=(const size_t value);

    // доступ
    T &operator*();
    const T &operator*() const;
    T &value();
    const T &value() const;
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

#endif // __ITERATOR_HPP__

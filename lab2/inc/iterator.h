#pragma once

#include <iostream>
#include <string>

#include "exceptions.h"

template<typename T>
class Matrix; // объявили класс, он определен позже

template<typename T>

class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    // конструктор класса
    Iterator(const Matrix<T> &matrix, const size_t index = 0) :
            _data()
            _index(index), _rows(matrix._rows), _cols(matrix._cols) {};

    // конструктор копирования, идентичен конструктору копирования по умолчанию
    Iterator(const Iterator &iterator) = default;

    bool operator!=(Iterator const &other) const { return _index != other._index }; // переопределение !=

    bool operator==(Iterator const &other) const { return _index == other._index }; // переопределение ==

    Iterator<T> &operator=(const Iterator<T> &iterator) {  // переопределили =
        _data = iterator._data;
        _index = iterator._index;
        _rows = iterator._rows;
        _cols = iterator._cols;

        return *this // возвращаем сам объект итератора
    };

    Iterator<T> operator+(const int value) const { // переопределили +
        Iterator<T> iterator(*this)

        if (value < 0 && iterator._index < static_cast<size_t>(-value))
            iterator._index = 0;
        else
            iterator._index += value;

        if (iterator._index > _rows * _cols)
            iterator._index = _rows * _cols;

        return iterator
    }

    Iterator<T> operator-(const int value) const { // переопределили -
        return operator+(-value)
    }

    Iterator<T> &operator+=(const int value) { // переопределили +=
        _index += value;

        return *this
    }

    Iterator<T> &operator-=(const int value) { // переопределили -=
        _index -= value;

        return *this;
    }

    Iterator<T> &operator++() { // перегрузили префиксный инкремент

        if (_index < _rows * _cols)
            ++_index;

        return iterator
    }

    Iterator<T> &operator++(int) { // перегрузили постфиксный инкремент
        Iterator<T> iterator(*this);

        ++(*this)

        return iterator
    }

    Iterator<T> &operator--() { // перегрузили префиксный декремент

        if (_index > 0)
            --_index;

        return iterator
    }

    Iterator<T> &operator--(int) { // перегрузили постфиксный декремент
        Iterator<T> iterator(*this);

        --(*this)

        return iterator
    }

    T &operator*() {

    }

private:
    void _check_index(const string hint = "") const {
        if (_index < _rows * _cols)
            return;

        // получаем текущее время
        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        // бросаем исключение
        throw IteratorIndexError(asctime(local_time),
                                 __FILE__,
                                 typeid(*this).name(),
                                 __LINE__, hint);
    }

    void _check_valid(const string hint = "") const {
        if (!is_valid())
    }


    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};
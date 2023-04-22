#pragma once

#include <iostream>
#include <string>

#include "exceptions.h"

template<typename T>
class Matrix; // объявили класс, он определен позже

template<typename T>
class ConstIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
    // конструктор класса
    ConstIterator(const Matrix<T> &matrix, const size_t index = 0) :
            _data(matrix._data),
            _index(index), _rows(matrix._rows),
            _cols(matrix._cols) {};

    // конструктор копирования, идентичен конструктору копирования по умолчанию
    ConstIterator(const Iterator &iterator) = default;

    bool operator!=(ConstIterator const &other) const { return _index != other._index }; // переопределение !=

    bool operator==(ConstIterator const &other) const { return _index == other._index }; // переопределение ==

    ConstIterator<T> operator+(const int value) const { // переопределили +
        Iterator <T> iterator(*this)

        if (value < 0 && iterator._index < static_cast<size_t>(-value))
            iterator._index = 0;
        else
            iterator._index += value;

        if (iterator._index > _rows * _cols)
            iterator._index = _rows * _cols;

        return iterator
    }

    ConstIterator<T> operator-(const int value) const { // переопределили -
        return operator+(-value)
    }

    ConstIterator<T> &operator+=(const int value) const { // переопределили +=
        _index += value;

        return *this
    }

    ConstIterator<T> &operator-=(const int value) const { // переопределили -=
        _index -= value;

        return *this;
    }

    ConstIterator<T> &operator++() const { // перегрузили префиксный инкремент

        if (_index < _rows * _cols)
            ++_index;

        return iterator
    }

    ConstIterator<T> &operator++(int) const { // перегрузили постфиксный инкремент
        Iterator <T> iterator(*this);

        ++(*this)

        return iterator
    }

    ConstIterator<T> &operator--() const { // перегрузили префиксный декремент

        if (_index > 0)
            --_index;

        return iterator
    }

    ConstIterator<T> &operator--(int) const { // перегрузили постфиксный декремент
        Iterator <T> iterator(*this);

        --(*this)

        return iterator
    }

    const T &operator*() const {
        _check_valid("Iterator points on nullptr");
        _check_index("Iterator doesn't in data bounds, while executing const operator*");

        std::shared_ptr <T> ptr = _data.lock();

        return *(ptr.get() + _index)
    }

    const T *operator->() const {
        _check_valid("Iterator points on nullptr");
        _check_index("Iterator doesn't in data bounds, while executing const operator*");

        std::shared_ptr <T> ptr = _data.lock();

        return ptr.get() + _index
    }


    operator bool() const { return _data.expired() }

    bool is_valid() const { return !_data.expired(); }

    bool is_end() const { return _index == _rows * _cols };

    Iterator <T> &next() const { return operator++() }

private:
    // метод для проверки индекса
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

    // метод для проверки данных на валидность
    void _check_valid(const string hint = "") const {
        if (is_valid())
            return;

        time_t cur_time = time(NULL);
        auto local_time = localtime(&cur_time);

        throw IteratorValidError(asctime(local_time),
                                 __FILE__,
                                 typeid(*this).name(),
                                 __LINE__, hint);
    }

    // данные, по которым идет итерация
    std::weak_ptr <T> _data = nullptr;

    size_t _index = 0;
    size_t _rows = 0;
    size_t _cols = 0;
};
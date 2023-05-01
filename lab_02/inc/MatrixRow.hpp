#ifndef __MATRIXROW_HPP__
#define __MATRIXROW_HPP__

#include <iostream>
#include <memory>

// класс будет шаблонным, то есть тип элемента строки матрицы будет определяться при создании
template <typename T>
class MatrixRow
{
public:
    explicit MatrixRow();                                         // конструктор без параметров
    explicit MatrixRow(const T *data_row, const size_t size_row); // конструктор создания строки матрицы

    ~MatrixRow() noexcept = default; // деструктор класса строки по умолчанию

    T &operator[](const size_t index);             // получение элемента строки через индексацию
    const T &operator[](const size_t index) const; // получение элемента строки через индексацию (константное)

    void reset(T *data_row, const size_t size_row); // переустановка новых данных
    void reset();                                   // сброс данных
private:
    std::shared_ptr<T[]> _data_row{nullptr}; // элементы строки
    size_t _size_row = 0;                    // количество элементов в строке
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// конструктро без параметров
MatrixRow<T>::MatrixRow() : _data_row(nullptr), _size_row(0)
{
}

template <typename T>
// конструктор создания строки матрицы
MatrixRow<T>::MatrixRow(const T *data_row, const size_t size_row) : _data_row(data_row), _size_row(size_row)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// получение элемента строки через индексацию
T &MatrixRow<T>::operator[](const size_t index)
{
    // позже добавить проверкку индекса
    return _data_row[index];
}

template <typename T>
// получение элемента строки через индексацию (константное)
const T &MatrixRow<T>::operator[](const size_t index) const
{
    // позже добавить проверкку индекса
    return _data_row[index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переустановка новых данных
void MatrixRow<T>::reset(T *data_row, const size_t size_row)
{
    _size_row = size_row;
    _data_row.reset(data_row);
}

template <typename T>
// сброс данных
void MatrixRow<T>::reset()
{
    _size_row = 0;
    _data_row.reset();
}

#endif // __MATRIXROW_HPP__
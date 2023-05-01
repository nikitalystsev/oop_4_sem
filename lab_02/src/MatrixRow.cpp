#include "MatrixRow.hpp"

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

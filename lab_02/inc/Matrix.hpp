#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <memory>

#include "MatrixBase.hpp" // класс матрицы будет наследоваться от базового класса
#include "MatrixRow.hpp"
#include "Iterator.hpp"

// класс будет шаблонным, то есть тип элемента матрицы будет определяться при создании
template <typename T>
class Matrix : public MatrixBase // наследуется от базового класса
{
    friend Iterator<T>;
public:
    // различные конструкторы класса Matrix
    explicit Matrix() = default; // конструктор без параметров по умолчанию
    explicit Matrix(const size_t rows = 0, const size_t cols = 0);
    explicit Matrix(const size_t rows, const size_t cols, const T &filler); // конструктор для заполнения матрицы filler-ом
    explicit Matrix(const size_t rows, const size_t columns, T **matrix);   // создание матрицы на основе си матрицы
    Matrix(std::initializer_list<std::initializer_list<T>> init_list);      // конструктор по списку инициализации
    explicit Matrix(const Matrix<T> &matrix);                               // конструктор копирования
    explicit Matrix(Matrix<T> &&matrix);                                    // конструктор перемещения

    ~Matrix() noexcept = default; // деструктор класса по умолчанию

    MatrixRow<T> operator[](size_t row);             // методы, возвращающие строку матрицы
    const MatrixRow<T> operator[](size_t row) const; // методы, возвращающие строку матрицы

    Iterator<T> begin();
    Iterator<T> end();

private:
    // атрибуты _rows и _cols не объявляю, поскольку они есть в базовом классе
    std::shared_ptr<MatrixRow<T>[]> _data;           // собственно сами данные (массив указателей на строки)
    void _matrix_alloc(const size_t rows, const size_t cols); // метод выделяет память под матрицы
};

///////////////////////////////////////////////////////////////////////////////////////////////////

// все конструкторы будут шаблонными, чтобы элементом матрицы мог быть любой тип данных
template <typename T>
// первый конструктор с параметрами. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols) : MatrixBase(rows, cols)
{
    _matrix_alloc(rows, cols); // выделяем память под матрицу
}

template <typename T>
// конструктор заполнения матрицы переданным значением. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T &filler) : MatrixBase(rows, cols)
{
    _matrix_alloc(rows, cols); // выделяем память под матрицу

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            _data[i][j] = filler;
}

template <typename T>
// конструктор создания матрицы на основе си матрицы. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols, T **matrix) : MatrixBase(rows, cols)
{
    // позже добавить проверку указателя
    _matrix_alloc(rows, cols); // выделяем память под матрицу

    for (size_t i = 0; i < rows; ++i)
    {
        // позже добавить проверку указателя
        for (size_t j = 0; j < cols; ++j)
            _data[i][j] = matrix[i][j];
    }
}

template <typename T>
// конструктор создания матрицы на основе списка инициализации.
// Конструктор базового класса не вызывается
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init_list)
{
    size_t rows = init_list.size();          // количество строк
    size_t cols = init_list.begin()->size(); // количество столбцов

    // добавить позже проверку, что количество столбцов во всех строках одинаковое

    _matrix_alloc(rows, cols); // выделяем память под матрицу

    _rows = rows;
    _cols = cols;

    size_t i = 0;

    for (const auto &i_list : init_list)
        for (const auto &elem : i_list)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }
}

template <typename T>
// конструктор копирования. Вызывается конструктор бзового класса
Matrix<T>::Matrix(const Matrix<T> &matrix) : MatrixBase(matrix._rows, matrix._cols)
{
    _matrix_alloc(matrix._rows, matrix._cols); // выделяем память под матрицу

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];
}

template <typename T>
// конструктор перемещения. Вызывается конструктор бзового класса
Matrix<T>::Matrix(Matrix &&matrix) : MatrixBase(matrix._rows, matrix._cols)
{
    _data = matrix._data;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
MatrixRow<T> Matrix<T>::operator[](size_t row)
{
    return _data[row];
}

template <typename T>
const MatrixRow<T> Matrix<T>::operator[](size_t row) const
{
    return _data[row];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Matrix<T>::_matrix_alloc(size_t rows, size_t cols)
{
    _data.reset(new MatrixRow<T>[rows]);

    for (size_t i = 0; i < rows; i++)
        _data[i].reset(new T[cols], cols);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Iterator<T> Matrix<T>::begin()
{
    return Iterator<T>(*this, 0);
}

template <typename T>
Iterator<T> Matrix<T>::end()
{
    return Iterator<T>(*this, _cols * _rows);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// вывод матрицы на экран
std::ostream &operator<<(std::ostream &out, const Matrix<T> &matrix)
{
    bool first_row = true;
    bool first_col = true;

    for (size_t i = 0; i < matrix.get_rows(); ++i)
    {
        first_col = true;
        if (!first_row)
            out << "\n";
        first_row = false;

        for (size_t j = 0; j < matrix.get_cols(); ++j)
        {
            if (!first_col)
                out << '\t';
            first_col = false;
            out << matrix[i][j];
        }
    }

    return out;
}
#endif // __MATRIX_HPP__
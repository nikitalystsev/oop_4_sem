#include "Matrix.hpp"

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
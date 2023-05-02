#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <memory>
#include <cmath>

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
    Matrix(const Matrix<T> &matrix);                                        // конструктор копирования
    explicit Matrix(Matrix<T> &&matrix);                                    // конструктор перемещения

    ~Matrix() noexcept = default; // деструктор класса по умолчанию

    MatrixRow<T> operator[](size_t row);             // методы, возвращающие строку матрицы
    const MatrixRow<T> operator[](size_t row) const; // методы, возвращающие строку матрицы

    // методы для итерации по матрицы (итерация по строкам)
    Iterator<T> begin();
    Iterator<T> end();

    Matrix<T> &operator=(const Matrix<T> &matrix);
    Matrix<T> &operator=(Matrix<T> &&matrix);
    Matrix<T> &operator=(std::initializer_list<std::initializer_list<T>> init_list);

    // математические операции с матрицами
    template <typename T2>
    decltype(auto) operator+(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator+(const T2 &elem) const noexcept;
    Matrix<T> &operator+=(const T &elem) noexcept;
    Matrix<T> &operator+=(const Matrix &matrix);

    template <typename T2>
    decltype(auto) add_matrix(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) add_elem(const T2 &elem) const noexcept;
    Matrix<T> &add_eq_elem(const T &elem) noexcept;
    Matrix<T> &add_eq_matrix(const Matrix &matrix);

    template <typename T2>
    decltype(auto) operator-(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator-(const T2 &elem) const noexcept;
    Matrix<T> &operator-=(const Matrix &matrix);
    Matrix<T> &operator-=(const T &elem) noexcept;

    template <typename T2>
    decltype(auto) sub_matrix(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) sub_elem(const T2 &elem) const noexcept;
    Matrix<T> &sub_eq_matrix(const Matrix &matrix);
    Matrix<T> &sub_eq_elem(const T &elem) noexcept;

    template <typename T2>
    decltype(auto) operator*(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator*(const T2 &elem) const noexcept;
    Matrix<T> &operator*=(const Matrix &matrix);
    Matrix<T> &operator*=(const T &elem) noexcept;

    template <typename T2>
    decltype(auto) mul_matrix(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) mul_elem(const T2 &elem) const noexcept;
    Matrix<T> &mul_eq_matrix(const Matrix &matrix);
    Matrix<T> &mul_eq_elem(const T &elem) noexcept;

    Matrix<T> operator-();
    Matrix<T> neg();

    // более сложные математические операции
    double determinant() const;
    Matrix<T> transpose();
    Matrix<T> identity();
    // Matrix<T> inverse();

    bool is_square() const;                                               // квадратная ли матрица
    void fill(Iterator<T> start, const Iterator<T> &end, const T &value); // заполнение матрицы значениями
    T &get_elem(size_t row, size_t col);
    const T &get_elem(size_t row, size_t col) const;

private:
    // атрибуты _rows и _cols не объявляю, поскольку они есть в базовом классе
    std::shared_ptr<MatrixRow<T>[]> _data;                                               // собственно сами данные (массив указателей на строки)
    std::shared_ptr<MatrixRow<T>[]> _matrix_alloc(const size_t rows, const size_t cols); // метод выделяет память под матрицы
};

///////////////////////////////////////////////////////////////////////////////////////////////////

// все конструкторы будут шаблонными, чтобы элементом матрицы мог быть любой тип данных
template <typename T>
// первый конструктор с параметрами. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols) : MatrixBase(rows, cols)
{
    _data = _matrix_alloc(rows, cols); // выделяем память под матрицу
}

template <typename T>
// конструктор заполнения матрицы переданным значением. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols, const T &filler) : MatrixBase(rows, cols)
{
    _data = _matrix_alloc(rows, cols); // выделяем память под матрицу

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            _data[i][j] = filler;
}

template <typename T>
// конструктор создания матрицы на основе си матрицы. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols, T **matrix) : MatrixBase(rows, cols)
{
    // позже добавить проверку указателя
    _data = _matrix_alloc(rows, cols); // выделяем память под матрицу

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

    std::cout << "Вызвался конструктор на основе списка инициализации\n\n";

    _data = _matrix_alloc(rows, cols); // выделяем память под матрицу

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
    _data = _matrix_alloc(matrix._rows, matrix._cols); // выделяем память под матрицу

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
std::shared_ptr<MatrixRow<T>[]> Matrix<T>::_matrix_alloc(size_t rows, size_t cols)
{
    std::shared_ptr<MatrixRow<T>[]> data = nullptr;

    data.reset(new MatrixRow<T>[rows]);

    for (size_t i = 0; i < rows; i++)
        data[i].reset(new T[cols], cols);

    return data;
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
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &matrix)
{
    _data = _matrix_alloc(matrix._rows, matrix._cols); // выделяем память под матрицу

    _rows = matrix._rows, _cols = matrix._cols;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] = matrix[i][j];

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&matrix)
{
    _data = matrix._data;
    _rows = matrix._rows;
    _cols = matrix._cols;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(std::initializer_list<std::initializer_list<T>> init_list)
{
    size_t cols = init_list.begin()->size();

    // добавить проверку на то, что количество элементов в каждой строке одинаковое

    size_t i = 0;
    for (const auto &ilist : init_list)
        for (const auto &elem : ilist)
        {
            _data[i / cols][i % cols] = elem;
            ++i;
        }

    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator+(const Matrix<T2> &matrix) const
{
    // добавить проверку размеров матрицы

    Matrix<decltype((*this)[0][0] + matrix[0][0])> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + matrix[i][j];

    return tmp;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator+(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] + elem)> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] + elem;

    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix &matrix)
{
    // добавить проверку размеров матрицы

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] += matrix[i][j];

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const T &elem) noexcept
{
    for (auto &element : *this)
        element += elem;

    return *this;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::add_matrix(const Matrix<T2> &matrix) const
{
    return operator+(matrix);
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::add_elem(const T2 &elem) const noexcept
{
    return operator+(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::add_eq_matrix(const Matrix &matrix)
{
    return operator+=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::add_eq_elem(const T &elem) noexcept
{
    return operator+=(elem);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator-(const Matrix<T2> &matrix) const
{
    // добавить проверку размеров матрицы

    Matrix<decltype((*this)[0][0] - matrix[0][0])> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] - matrix[i][j];

    return tmp;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator-(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] - elem)> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] - elem;

    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix &matrix)
{
    // проверка размеров матрицы

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            _data[i][j] -= matrix[i][j];

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const T &elem) noexcept
{
    for (auto &element : *this)
        element -= elem;

    return *this;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::sub_matrix(const Matrix<T2> &matrix) const
{
    return operator-(matrix);
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::sub_elem(const T2 &elem) const noexcept
{
    return operator-(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::sub_eq_matrix(const Matrix &matrix)
{
    return operator-=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::sub_eq_elem(const T &elem) noexcept
{
    return operator-=(elem);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator*(const Matrix<T2> &matrix) const
{
    // проверка аргументов матрицы для матричного умножения

    Matrix<decltype((*this)[0][0] * matrix[0][0])> tmp(_rows, matrix._cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < matrix._cols; ++j)
            for (size_t k = 0; k < _cols; ++k)
                tmp[i][j] += _data[i][k] * matrix[k][j];

    return tmp;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::operator*(const T2 &elem) const noexcept
{
    Matrix<decltype((*this)[0][0] * elem)> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = _data[i][j] * elem;

    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix &matrix)
{
    // проверить размеры матрицы

    Matrix<T> tmp(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            for (size_t k = 0; k < _rows; ++k)
                tmp[i][j] += _data[i][k] * matrix[k][j];

    *this = tmp;

    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T &elem) noexcept
{
    for (auto &element : *this)
        element *= elem;

    return *this;
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::mul_matrix(const Matrix<T2> &matrix) const
{
    return operator*(matrix);
}

template <typename T>
template <typename T2>
decltype(auto) Matrix<T>::mul_elem(const T2 &elem) const noexcept
{
    return operator*(elem);
}

template <typename T>
Matrix<T> &Matrix<T>::mul_eq_matrix(const Matrix &matrix)
{
    return operator*=(matrix);
}

template <typename T>
Matrix<T> &Matrix<T>::mul_eq_elem(const T &elem) noexcept
{
    return operator*=(elem);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Matrix<T> Matrix<T>::operator-()
{
    Matrix<T> tmp(_rows, _cols);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[i][j] = -_data[i][j];

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::neg()
{
    return operator-();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
double Matrix<T>::determinant() const
{
    if (this->get_rows() == 2)
        return _data[0][0] * _data[1][1] - _data[1][0] * _data[0][1];

    if (this->get_rows() == 1)
        return _data[0][0];

    Matrix<T> tmp(*this); // вызываю конструктор копирования

    double det = 1;

    for (size_t i = 0; i < tmp.get_rows(); ++i)
    {
        double mx = fabs(tmp[i][i]);
        size_t idx = i;

        for (size_t j = i + 1; j < tmp.get_rows(); ++j)
            if (mx < fabs(tmp[i][j]))
            {
                mx = fabs(tmp[i][j]);
                idx = j;
            }

        if (idx != i)
        {
            for (size_t j = i; j < tmp.get_rows(); ++j)
            {
                T t = tmp[j][i];
                tmp[j][i] = tmp[j][idx];
                tmp[j][idx] = t;
            }
            det = -det;
        }

        for (size_t k = i + 1; k < tmp.get_rows(); ++k)
        {
            T t = tmp[k][i] / tmp[i][i];

            for (size_t j = i; j < tmp.get_rows(); ++j)
                tmp[k][j] -= tmp[i][j] * t;
        }
    }

    for (size_t i = 0; i < tmp.get_rows(); ++i)
        det *= tmp[i][i];

    return det;
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> tmp(_cols, _rows);

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            tmp[j][i] = _data[i][j];

    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::identity()
{
    Matrix<T> tmp(_cols, _rows);

    for (size_t i = 0; i < tmp.get_rows(); i++)
        for (size_t j = 0; j < tmp.get_cols(); j++)
            tmp[i][j] = i == j;

    return tmp;
}

// template <typename T>
// Matrix<T> Matrix<T>::inverse()
// {
//     T temp;

//     Matrix<T> iden = identity();
//     Matrix<T> tmp(*this);

//     std::cout << "закончил работу\n\n";

//     for (size_t k = 0; k < tmp.get_rows(); k++)
//     {
//         temp = tmp[k][k];

//         std::cout << "в цикле\n\n";

//         for (size_t j = 0; j < tmp.get_rows(); j++)
//         {
//             tmp[k][j] /= temp;
//             iden[k][j] /= temp;
//         }

//         for (size_t i = k + 1; i < tmp.get_rows(); i++)
//         {
//             temp = tmp[i][k];

//             for (size_t j = 0; j < tmp.get_rows(); j++)
//             {
//                 tmp[i][j] -= tmp[k][j] * temp;
//                 iden[i][j] -= iden[k][j] * temp;
//             }
//         }
//     }

//     std::cout << "закончил работу\n\n";

//     for (int k = tmp.get_rows() - 1; k > 0; k--)
//     {
//         for (int i = k - 1; i >= 0; i--)
//         {
//             temp = tmp[i][k];

//             for (size_t j = 0; j < tmp.get_rows(); j++)
//             {
//                 tmp[i][j] -= tmp[k][j] * temp;
//                 iden[i][j] -= iden[k][j] * temp;
//             }
//         }
//     }

//     std::cout << "закончил работу\n\n";

//     for (size_t i = 0; i < tmp.get_rows(); i++)
//         for (size_t j = 0; j < tmp.get_rows(); j++)
//             tmp[i][j] = iden[i][j];

//     std::cout << "закончил работу\n\n";

//     return tmp;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// квадратная ли матрица
bool Matrix<T>::is_square() const
{
    return _rows == _cols;
}

template <typename T>
// заполнить часть матрицы значениями
void Matrix<T>::fill(Iterator<T> start, const Iterator<T> &end, const T &value)
{
    for (auto it = start; it < end; ++it)
        *it = value;
}

template <typename T>
// получить элемент матрицы
T &Matrix<T>::get_elem(size_t row, size_t col)
{
    return _data[row][col];
}

template <typename T>
// получить элемент матрицы
const T &Matrix<T>::get_elem(size_t row, size_t col) const
{
    return _data[row][col];
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
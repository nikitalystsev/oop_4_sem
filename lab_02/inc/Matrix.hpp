#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <memory>
#include <cmath>

#include "MatrixBase.hpp" // класс матрицы будет наследоваться от базового класса
#include "Iterator.hpp"
#include "ConstIterator.hpp"
#include "MatrixExceptions.hpp"

// класс будет шаблонным, то есть тип элемента матрицы будет определяться при создании
template <typename T>
class Matrix : public MatrixBase // наследуется от базового класса
{
public:
    class MatrixRow; // обьявляем класс MatrixRow
    friend Iterator<T>;
    friend ConstIterator<T>;

public:
    using value_type = T;

    // различные конструкторы класса Matrix
    Matrix() = default;
    explicit Matrix(const size_t rows = 0, const size_t cols = 0);
    Matrix(const size_t rows, const size_t cols, const T &filler);     // конструктор для заполнения матрицы filler-ом
    Matrix(const size_t rows, const size_t columns, T **matrix);       // создание матрицы на основе си матрицы
    Matrix(std::initializer_list<std::initializer_list<T>> init_list); // конструктор по списку инициализации
    explicit Matrix(const Matrix<T> &matrix);                          // конструктор копирования
    Matrix(Matrix<T> &&matrix);                                        // конструктор перемещения

    ~Matrix() noexcept = default; // деструктор класса по умолчанию

    MatrixRow operator[](size_t row);             // методы, возвращающие строку матрицы
    const MatrixRow operator[](size_t row) const; // методы, возвращающие строку матрицы

    // методы для итерации по матрицы (итерация по строкам)
    Iterator<T> begin();
    Iterator<T> end();
    ConstIterator<T> begin() const;
    ConstIterator<T> end() const;
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;

    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;

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
    Matrix<double> inverse();
    bool is_square() const; // квадратная ли матрица
    void fill(Iterator<T> start, const Iterator<T> &end, const T &value); // заполнение матрицы значениями

    T &get_elem(size_t row, size_t col);
    const T &get_elem(size_t row, size_t col) const;

private:
    // атрибуты _rows и _cols не объявляю, поскольку они есть в базовом классе
    std::shared_ptr<MatrixRow[]> _data;                                               // собственно сами данные (массив указателей на строки)
    std::shared_ptr<MatrixRow[]> _matrix_alloc(const size_t rows, const size_t cols); // метод выделяет память под матрицы

    void _check_index(size_t pos, size_t limit) const;
    void _check_sizes(const Matrix &matrix) const;
    void _check_mult_sizes(const Matrix &matrix) const;

    void _move_row(size_t from, size_t to);
    void _move_col(size_t from, size_t to);

public: // для описания строки матрицы как подкласса самой матрицы
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
void _check_ptr(T ptr)
{
    if (ptr)
        return;

    throw InvalidArgument(__FILE__, "Non-class", __LINE__, "nullptr as a ptr of c-matrix");
}

template <typename T>
// конструктор создания матрицы на основе си матрицы. Вызывается конструктор базового класса
Matrix<T>::Matrix(const size_t rows, const size_t cols, T **matrix) : MatrixBase(rows, cols)
{
    _check_ptr(matrix); // проверка указателя

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

    for (const auto &ilist : init_list)
        if (ilist.size() != cols)
        {
            throw InvalidArgument(__FILE__, typeid(*this).name(),
                                  __LINE__, "Bad initializer list");
        }

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
Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row)
{
    return _data[row];
}

template <typename T>
const Matrix<T>::MatrixRow Matrix<T>::operator[](size_t row) const
{
    return _data[row];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::shared_ptr<typename Matrix<T>::MatrixRow[]> Matrix<T>::_matrix_alloc(size_t rows, size_t cols)
{
    std::shared_ptr<MatrixRow[]> data = nullptr;

    try
    {
        data.reset(new MatrixRow[rows]);

        for (size_t i = 0; i < rows; i++)
            data[i].reset(new T[cols], cols);
    }
    catch (std::bad_alloc &err)
    {
        throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, "_matrix_alloc function error");
    }

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
template <typename T>
ConstIterator<T> Matrix<T>::begin() const
{
    return ConstIterator<T>(*this, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::end() const
{
    return ConstIterator<T>(*this, _cols * _rows);
}

template <typename T>
ConstIterator<T> Matrix<T>::cbegin() const
{
    return ConstIterator<T>(*this, 0);
}

template <typename T>
ConstIterator<T> Matrix<T>::cend() const
{
    return ConstIterator<T>(*this, _cols * _rows);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Matrix<T>::operator==(const Matrix &matrix) const
{
    if ((_rows != matrix._rows) || (_cols != matrix._cols))
        return false;

    for (size_t i = 0; i < _rows; ++i)
        for (size_t j = 0; j < _cols; ++j)
            if (_data[i][j] != matrix[i][j])
                return false;

    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &matrix) const
{
    return !operator==(matrix);
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

    for (const auto &ilist : init_list)
        if (ilist.size() != cols)
        {
            throw InvalidArgument(__FILE__, typeid(*this).name(), __LINE__, "Bad initializer list");
        }

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
    _check_sizes(matrix);

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
    _check_sizes(matrix);

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
    _check_sizes(matrix);

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
    _check_sizes(matrix);

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
    _check_mult_sizes(matrix);

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
    _check_sizes(matrix);
    _check_mult_sizes(matrix);

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
Matrix<T> operator+(const T &elem, const Matrix<T> &matrix)
{
    return matrix + elem;
}

template <typename T>
Matrix<T> operator-(const T &elem, const Matrix<T> &matrix)
{
    return matrix - elem;
}

template <typename T>
Matrix<T> operator*(const T &elem, const Matrix<T> &matrix)
{
    return matrix * elem;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
double Matrix<T>::determinant() const
{
    if (!is_square())
    {
        throw InvalidState(__FILE__, typeid(*this).name(), __LINE__, "Matrix should be square to get determinant;");
    }

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

template <typename T>
Matrix<double> Matrix<T>::inverse()
{
    T temp;

    Matrix<T> iden = identity();
    Matrix<double> tmp(*this);

    for (size_t k = 0; k < tmp.get_rows(); k++)
    {
        temp = tmp[k][k];

        for (size_t j = 0; j < tmp.get_rows(); j++)
        {
            tmp[k][j] /= temp;
            iden[k][j] /= temp;
        }

        for (size_t i = k + 1; i < tmp.get_rows(); i++)
        {
            temp = tmp[i][k];

            for (size_t j = 0; j < tmp.get_rows(); j++)
            {
                tmp[i][j] -= tmp[k][j] * temp;
                iden[i][j] -= iden[k][j] * temp;
            }
        }
    }

    for (int k = tmp.get_rows() - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = tmp[i][k];

            for (size_t j = 0; j < tmp.get_rows(); j++)
            {
                tmp[i][j] -= tmp[k][j] * temp;
                iden[i][j] -= iden[k][j] * temp;
            }
        }
    }

    for (size_t i = 0; i < tmp.get_rows(); i++)
        for (size_t j = 0; j < tmp.get_rows(); j++)
            tmp[i][j] = iden[i][j];

    return tmp;
}

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
    for (Iterator<T> it = start; it < end; ++it)
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
void Matrix<T>::_check_index(size_t pos, size_t limit) const
{
    if (pos <= limit)
        return;

    throw IndexError(__FILE__, typeid(*this).name(), __LINE__, "Index is bigger than sizes");
}

template <typename T>
void Matrix<T>::_check_sizes(const Matrix<T> &matrix) const
{
    if (_rows == matrix._rows &&_cols = matrix._cols)
        return;

    throw IncompatibleElements(__FILE__, typeid(*this).name(), __LINE__, "Different matrix sizes");
}

template <typename T>
void Matrix<T>::_check_mult_sizes(const Matrix<T> &matrix) const
{
    if (_cols == matrix._rows)
        return;

    throw IncompatibleElements(__FILE__, typeid(*this).name(), __LINE__,
                               "Bad sizes of matrices for multiplication");
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Matrix<T>::_move_row(size_t from, size_t to)
{
    auto tmp = _data[from];

    for (size_t i = from; i > to; --i)

        _data[i] = _data[i - 1];

    for (size_t i = from; i < to; ++i)
        _data[i] = _data[i + 1];

    _data[to] = tmp;
}

template <typename T>
void Matrix<T>::_move_col(size_t from, size_t to)
{
    for (size_t j = 0; j < _rows; ++j)
    {
        auto tmp = _data[j][from];

        for (size_t i = from; i > to; --i)
            _data[j][i] = _data[j][i - 1];

        for (size_t i = from; i < to; ++i)
            _data[j][i] = _data[j][i + 1];

        _data[j][to] = tmp;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// конструктро без параметров
Matrix<T>::MatrixRow::MatrixRow() : _data_row(nullptr), _size_row(0)
{
}

template <typename T>
// конструктор создания строки матрицы
Matrix<T>::MatrixRow::MatrixRow(const T *data_row, const size_t size_row) : _data_row(data_row), _size_row(size_row)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// получение элемента строки через индексацию
T &Matrix<T>::MatrixRow::operator[](const size_t index)
{
    // позже добавить проверкку индекса
    return _data_row[index];
}

template <typename T>
// получение элемента строки через индексацию (константное)
const T &Matrix<T>::MatrixRow::operator[](const size_t index) const
{
    // позже добавить проверкку индекса
    return _data_row[index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
// переустановка новых данных
void Matrix<T>::MatrixRow::reset(T *data_row, const size_t size_row)
{
    _size_row = size_row;
    _data_row.reset(data_row);
}

template <typename T>
// сброс данных
void Matrix<T>::MatrixRow::reset()
{
    _size_row = 0;
    _data_row.reset();
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
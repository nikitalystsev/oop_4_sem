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
    // class MatrixRow; // обьявляем класс MatrixRow
    // friend Iterator<T>;
    // friend ConstIterator<T>;

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

    // MatrixRow operator[](size_t row);             // методы, возвращающие строку матрицы
    // const MatrixRow operator[](size_t row) const; // методы, возвращающие строку матрицы

    // // методы для итерации по матрицы (итерация по строкам)
    // Iterator<T> begin();
    // Iterator<T> end();
    // ConstIterator<T> begin() const;
    // ConstIterator<T> end() const;
    // ConstIterator<T> cbegin() const;
    // ConstIterator<T> cend() const;

    // bool operator==(const Matrix &matrix) const;
    // bool operator!=(const Matrix &matrix) const;

    // Matrix<T> &operator=(const Matrix<T> &matrix);
    // Matrix<T> &operator=(Matrix<T> &&matrix);
    // Matrix<T> &operator=(std::initializer_list<std::initializer_list<T>> init_list);

    // // математические операции с матрицами
    // template <typename T2>
    // decltype(auto) operator+(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) operator+(const T2 &elem) const noexcept;
    // Matrix<T> &operator+=(const T &elem) noexcept;
    // Matrix<T> &operator+=(const Matrix &matrix);

    // template <typename T2>
    // decltype(auto) add_matrix(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) add_elem(const T2 &elem) const noexcept;
    // Matrix<T> &add_eq_elem(const T &elem) noexcept;
    // Matrix<T> &add_eq_matrix(const Matrix &matrix);

    // template <typename T2>
    // decltype(auto) operator-(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) operator-(const T2 &elem) const noexcept;
    // Matrix<T> &operator-=(const Matrix &matrix);
    // Matrix<T> &operator-=(const T &elem) noexcept;

    // template <typename T2>
    // decltype(auto) sub_matrix(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) sub_elem(const T2 &elem) const noexcept;
    // Matrix<T> &sub_eq_matrix(const Matrix &matrix);
    // Matrix<T> &sub_eq_elem(const T &elem) noexcept;

    // template <typename T2>
    // decltype(auto) operator*(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) operator*(const T2 &elem) const noexcept;
    // Matrix<T> &operator*=(const Matrix &matrix);
    // Matrix<T> &operator*=(const T &elem) noexcept;

    // template <typename T2>
    // decltype(auto) mul_matrix(const Matrix<T2> &matrix) const;
    // template <typename T2>
    // decltype(auto) mul_elem(const T2 &elem) const noexcept;
    // Matrix<T> &mul_eq_matrix(const Matrix &matrix);
    // Matrix<T> &mul_eq_elem(const T &elem) noexcept;

    // Matrix<T> operator-();
    // Matrix<T> neg();

    // // более сложные математические операции
    // double determinant() const;
    // Matrix<T> transpose();
    // Matrix<T> identity();
    // Matrix<double> inverse();
    // bool is_square() const; // квадратная ли матрица
    // void fill(Iterator<T> start, const Iterator<T> &end, const T &value); // заполнение матрицы значениями

    // T &get_elem(size_t row, size_t col);
    // const T &get_elem(size_t row, size_t col) const;

private:
    // // атрибуты _rows и _cols не объявляю, поскольку они есть в базовом классе
    // std::shared_ptr<MatrixRow[]> _data;                                               // собственно сами данные (массив указателей на строки)
    // std::shared_ptr<MatrixRow[]> _matrix_alloc(const size_t rows, const size_t cols); // метод выделяет память под матрицы

    // void _check_index(size_t pos, size_t limit) const;
    // void _check_sizes(const Matrix &matrix) const;
    // void _check_mult_sizes(const Matrix &matrix) const;

    // void _move_row(size_t from, size_t to);
    // void _move_col(size_t from, size_t to);

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

        T *get_address() { return _data_row.get(); }
        const T *get_address() const { return _data_row.get(); }
    };
};

#endif // __MATRIX_HPP__
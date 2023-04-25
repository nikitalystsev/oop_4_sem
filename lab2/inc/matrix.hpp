#pragma once
#include <iostream>
#include <iterator>
#include <memory>
#include "matrix_base.hpp"
#include "exception.hpp"
#include "const_iterator.hpp"
#include "iterator.hpp"

template <typename T>
using SharedPtr = std::shared_ptr<T>;
using string = std::string;

template <typename T>
class Matrix: public MatrixBase
{
public:
    class MatrixRow;
    friend Iterator<T>;
    friend ConstIterator<T>;

public:
    explicit Matrix(size_t rows = 0, size_t columns = 0);
    Matrix(size_t rows, size_t columns, const T &filler);
    
    Matrix(size_t rows, size_t columns, T **matrix);
    Matrix(std::initializer_list<std::initializer_list<T> > init_list);
    explicit Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);

    virtual ~Matrix() = default;

    // операции над матрицами
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;

    Matrix<T> &operator=(const Matrix &matrix);
    Matrix<T> &operator=(Matrix &&matrix);
    Matrix<T> &operator=(std::initializer_list<std::initializer_list<T> > init_list);

    template <typename T2>
    decltype(auto) operator+(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator+(const T2 &elem) const noexcept;
    Matrix<T> &operator+=(const T &elem) noexcept;
    Matrix<T> &operator+=(const Matrix &matrix);

    template <typename T2>
    decltype(auto) operator-(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator-(const T2 &elem) const noexcept;
    Matrix<T> &operator-=(const T &elem) noexcept;
    Matrix<T> &operator-=(const Matrix &matrix);

    template <typename T2>
    decltype(auto) operator*(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator*(const T2 &elem) const noexcept;
    Matrix<T> &operator*=(const T &elem) noexcept;
    Matrix<T> &operator*=(const Matrix &matrix);

    template <typename T2>
    decltype(auto) operator/(const Matrix<T2> &matrix) const;
    template <typename T2>
    decltype(auto) operator/(const T2 &elem) const;
    Matrix<T> &operator/=(const T &elem);
    Matrix<T> &operator/=(const Matrix &matrix);

    T determinant() const; // определитель матрицы
    void transpose(); // транспонирование матрицы
    void inverse(); // обратная матрица
    bool is_square() const; // квадратная ли матрица
    void fill(Iterator<T> start, const Iterator<T> &end, const T &value); // заполнение матрицы значениями

    ConstIterator<T> begin() const;
    ConstIterator<T> end() const;
    Iterator<T> begin();
    Iterator<T> end();
    ConstIterator<T> cbegin() const;
    ConstIterator<T> cend() const;

    MatrixRow operator[](size_t row);
    const MatrixRow operator[](size_t row) const;

    T &get_elem(size_t row, size_t col);
    const T &get_elem(size_t row, size_t col) const;

    T &operator()(size_t row, size_t col);
    const T &operator()(size_t row, size_t col) const;


private:
    SharedPtr<MatrixRow[]> _data { nullptr };
    SharedPtr<MatrixRow[]> _mem_alloc(size_t rows, size_t cols);
    void _move_row(size_t from, size_t to);
    void _move_col(size_t from, size_t to);
    void _check_index(size_t pos, size_t limit) const;
    void _check_sizes(const Matrix &matrix) const;
    void _check_mult_sizes(const Matrix &matrix) const;

public:
    // подкласс матрицы строки
    class MatrixRow 
    {
        friend Iterator<T>;
        friend ConstIterator<T>;
    public:
        MatrixRow(T *data, const size_t size): _data(data), _size(size) {}
        MatrixRow(): _data(nullptr), _size(0) {}
        T &operator[](size_t index);
        const T &operator[](size_t index) const;
        void reset(T *data, const size_t size);
        void reset();
        
    private:
        SharedPtr<T[]> _data = nullptr;
        size_t _size = 0;
        T *getAddr() { return _data.get(); };
        const T *getAddr() const { return _data.get(); };
    
    };

};

#include "../src/matrix_construct.hpp"
#include "../src/matrix_eqo.hpp"
#include "../src/matrix_iterators.hpp"
#include "../src/matrix_method.hpp"
#include "../src/matrix_operators.hpp"
#include "../src/matrix_private.hpp"
#include "../src/matrix_row.hpp"

#ifndef __MATRIXBASE_HPP__
#define __MATRIXBASE_HPP__

#include <cstddef> // для size_t

class MatrixBase // описание класса
{
public: // публичные атрибуты
    // explicit для запрета неявного преобразования типа
    // конструктор базового класса
    explicit MatrixBase(size_t rows = 0, size_t cols = 0) : _rows(rows), _cols(cols) {}

    // virtual значит метод, который м/б потом переопределен
    // константные, то есть не изменяющие состояния объекта, и не кидающие исключений
    virtual size_t get_rows() const noexcept { return _rows; }; // метод для получения количества строк матрицы

    virtual size_t get_cols() const noexcept { return _cols; }; // метод для получения количества столбцов матрицы

    virtual ~MatrixBase() = default; // деструктор класса по умолчанию

protected:            // защишенные атрибуты (доступны дочерним классам)
    size_t _rows = 0; // количество строк матрицы
    size_t _cols = 0; // количество столбцов матрицы
};

#endif // __MATRIXBASE_HPP__
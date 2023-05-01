#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <iostream>
#include <memory>

#include "MatrixBase.hpp" // класс матрицы будет наследоваться от базового класса
#include "MatrixRow.hpp"

// класс будет шаблонным, то есть тип элемента матрицы будет определяться при создании
template <typename T>
class Matrix : public MatrixBase // наследуется от базового класса
{
public:
    // различные конструкторы класса Matrix
    explicit Matrix() = default; // конструктор без параметров по умолчанию
    explicit Matrix(const size_t rows = 0, const size_t cols = 0);
    explicit Matrix(const size_t rows, const size_t cols, const T &filler);     // конструктор для заполнения матрицы filler-ом
    explicit Matrix(const size_t rows, const size_t columns, T **matrix);       // создание матрицы на основе си матрицы
    explicit Matrix(std::initializer_list<std::initializer_list<T>> init_list); // конструктор по списку инициализации
    explicit Matrix(const Matrix<T> &matrix);                                   // конструктор копирования
    explicit Matrix(Matrix<T> &&matrix);                                        // конструктор перемещения

    ~Matrix() noexcept = default; // деструктор класса по умолчанию

private:
    // атрибуты _rows и _cols не объявляю, поскольку они есть в базовом классе
    std::shared_ptr<MatrixRow<T>[]> _data{nullptr};           // собственно сами данные (массив указателей на строки)
    void _matrix_alloc(const size_t rows, const size_t cols); // метод выделяет память под матрицы
};

#endif // __MATRIX_HPP__
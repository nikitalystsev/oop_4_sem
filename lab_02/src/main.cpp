#include <iostream>
#include "Matrix.hpp"

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

int main()
{
    std::cout << "Тестирование конструкторов создания матрицы:\n\n";

    std::cout << "Конструктор с двумя числами типа size_t:\n";

    Matrix<int> my_matrix(2, 3, 4);

    std::cout << my_matrix << "\n\n";

    return 0;
}

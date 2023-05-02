#include <iostream>
#include "Matrix.hpp"

int main()
{
    std::cout << "Тестирование конструкторов создания матрицы:\n\n";
    std::cout << "Конструктор с двумя числами типа size_t:\n";
    Matrix<int> my_matrix(2, 3, 4);
    std::cout << my_matrix << "\n\n";

    std::cout << "Тестирование итератора матрицы:\n\n";
    Matrix<int> new_matrix = {{0, 3, -1, 1},
                              {1, 2, 0, 0},
                              {0, 4, 3, 5},
                              {2, -1, -4, -2}};
    // Matrix<int> new_matrix(3, 3, 7);
    std::cout << new_matrix << "\n\n";
    std::cout << "\n\n";

    std::cout << "Проверка begin и end (new_matrix):\n";
    for (auto it = new_matrix.begin(); it < new_matrix.end(); it.next())
        std::cout << *it << "; ";

    std::cout << "\n\n";

    Matrix<int> transpose = new_matrix.transpose();

    std::cout << transpose << "\n\n";

    return 0;
}

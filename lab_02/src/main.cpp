#include <iostream>
#include "Matrix.hpp"

// int inversion_matrix(matrix_t *const matrix)
// {
//     double temp;

//     matrix_t iden;
//     iden.rows = matrix->rows;
//     iden.cols = matrix->cols;

//     if (matrix_alloc(&iden) != 0)
//         return ERR_ALLOC_MATRIX;

    // for (size_t i = 0; i < matrix->rows; i++)
    //     for (size_t j = 0; j < matrix->rows; j++)
    //         iden.matrix[i][j] = i == j;

    // for (size_t k = 0; k < matrix->rows; k++)
    // {
    //     temp = matrix->matrix[k][k];

    //     for (size_t j = 0; j < matrix->rows; j++)
    //     {
    //         matrix->matrix[k][j] /= temp;
    //         iden.matrix[k][j] /= temp;
    //     }

    //     for (size_t i = k + 1; i < matrix->rows; i++)
    //     {
    //         temp = matrix->matrix[i][k];

    //         for (size_t j = 0; j < matrix->rows; j++)
    //         {
    //             matrix->matrix[i][j] -= matrix->matrix[k][j] * temp;
    //             iden.matrix[i][j] -= iden.matrix[k][j] * temp;
    //         }
    //     }
    // }

//     for (int k = matrix->rows - 1; k > 0; k--)
//     {
//         for (int i = k - 1; i >= 0; i--)
//         {
//             temp = matrix->matrix[i][k];

//             for (size_t j = 0; j < matrix->rows; j++)
//             {
//                 matrix->matrix[i][j] -= matrix->matrix[k][j] * temp;
//                 iden.matrix[i][j] -= iden.matrix[k][j] * temp;
//             }
//         }
//     }

//     for (size_t i = 0; i < matrix->rows; i++)
//         for (size_t j = 0; j < matrix->rows; j++)
//             matrix->matrix[i][j] = iden.matrix[i][j];

//     matrix_free(iden.matrix, iden.rows);

//     return EXIT_SUCCESS;
// }

int main()
{
    std::cout << "Тестирование конструкторов создания матрицы:\n\n";
    std::cout << "Конструктор с двумя числами типа size_t:\n";
    Matrix<int> my_matrix(2, 3, 4);
    std::cout << my_matrix << "\n\n";

    std::cout << "Тестирование итератора матрицы:\n\n";
    Matrix<int> new_matrix = {{1, 3, -1, 1},
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

    Matrix<int> neg_matrix = new_matrix.neg();

    std::cout << new_matrix << "\n\n";

    return 0;
}

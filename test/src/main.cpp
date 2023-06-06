#include <iostream>
#include <string>
#include "Matrix.hpp"

using string = std::string;

int main()
{
    std::cout << "Тестирование конструкторов создания матрицы:\n\n";

    // Matrix<float> matrix1; нельзя
    Matrix<int> matrix2(2, 2);
    Matrix<int> matrix3(2, 2, 5);
    int **m = new int *[2];
    for (int i = 0; i < 2; ++i)
    {
        m[i] = new int[2];
        for (int j = 0; j < 2; ++j)
            m[i][j] = i + j;
    }
    Matrix<int> matrix4{2, 2, m};

    for (int i = 0; i < 2; ++i)
        delete[] m[i];
    delete[] m;
    Matrix<int> matrix5({{1, 2, 3},
                         {4, 5, 6}});
    // try
    // {
    //     std::cout << "Матрица с отрицательными количеством строк:\n";
    //     Matrix<int> err_m(-1, 2);
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cerr << err.what() << "\n\n";
    // }

    // size_t row = 2, col = 3;
    // std::cout << "Конструктор с двумя числами типа size_t:\n";
    // Matrix<int> my_matrix(row, col, 4);
    // std::cout << my_matrix << "\n\n";

    const size_t a = 2;
    const size_t b = 2;
    // const size_t c = 3;

    std::cout << "Проверка конструктора для списка инициализации:\n";
    Matrix<int> my_matrix3(a, b);
    // // std::cout << my_matrix3 << "\n\n";
    // Matrix<int> my_matrix4({{1, 2, 3},
    //                         {4, 5, 6}});
    // std::cout << "Проверка булевых операторов == и !=:\n";
    // if (my_matrix4 != my_matrix3)
    //     std::cout << "матрицы не равны"
    //               << "\n\n";
    // else
    //     std::cout << "матрицы равны"
    //               << "\n\n";

    // std::cout << "Получение элемента матрицы:\n\n";
    // Matrix<string> new_matrix = {{"a1", "a2", "a3"},
    //                              {"b1", "b2", "b3"},
    //                              {"c1", "c2", "c3"}};
    // std::cout << "new_matrix: \n"
    //           << new_matrix << "\n\n";

    // std::cout << "new_matrix[1][1] and new_matrix.get_elem(1, 1)\n";
    // std::cout << new_matrix[1][1] << " and " << new_matrix.get_elem(1, 1) << "\n\n";

    // std::cout << "new_matrix[1][1] = new1 and new_matrix.get_elem(1, 2) = new2\n";
    // new_matrix[1][1] = "new1";
    // new_matrix.get_elem(1, 2) = "new2";
    // std::cout << "new_matrix[1][1] = " << new_matrix[1][1] << ", new_matrix[1][2] = " << new_matrix[1][2] << "\n\n";

    // std::cout << "Элементы матрицы new_matrix:\n";
    // for (const auto &elem : new_matrix)
    //     std::cout << elem << ' ';
    // std::cout << "\n\n";

    // std::cout << "Проверка определителя матрицы:\n\n";
    // Matrix<double> my_matrix4 = {
    //     {2, -1, 0}, {0, 2, -1}, {-1, -1, 1}};

    // std::cout << "inverse: " << my_matrix4.inverse() << "\n\n";

    // std::cout << "Заполнение элементов матрицы (последняя линия):\n";
    // new_matrix.fill(new_matrix.end() - static_cast<int>(new_matrix.get_cols()), new_matrix.end(), "0");
    // std::cout << new_matrix << "\n\n";

    // std::cout << "Константная матрица:\n";
    // const Matrix<string> const_m = {{"11", "12", "13"},
    //                                 {"21", "22", "23"}};
    // std::cout << "Range-based for cycle for const matrix:\n";
    // for (const auto &elem : const_m)
    //     std::cout << elem << "; ";
    // std::cout << "\n\n";

    // std::cout << "Проверка cbegin и cend к не константному объекту (new_matrix):\n";
    // for (auto it = new_matrix.cbegin(); it < new_matrix.cend(); it++)
    //     std::cout << *it << "; ";
    // std::cout << "\n\n";

    // std::cout << "Математические операции:\n\n";
    // Matrix<double> math_matrix = {{1, 2, 3, 4},
    //                               {7, 9, 11, 13},
    //                               {4, 2, 0, -2},
    //                               {1, 4, 7, 10}};
    // std::cout << "math_matrix: \n";
    // std::cout << math_matrix << "\n\n";

    // std::cout << "Операция: math_matrix += 2.5;\n";
    // math_matrix += 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << math_matrix << "\n\n";

    // std::cout << "Операция: math_matrix -= 2.5;\n";
    // math_matrix -= 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << math_matrix << "\n\n";

    // std::cout << "Операция: math_matrix *= 2.5;\n";
    // math_matrix *= 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << math_matrix << "\n\n";

    // Matrix<double> tmp;

    // std::cout << "Операция: tmp = math_matrix + 2.5;\n";
    // tmp = math_matrix + 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << tmp << "\n\n";

    // std::cout << "Операция: tmp = math_matrix - 2.5;\n";
    // tmp = math_matrix - 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << tmp << "\n\n";

    // std::cout << "Операция: tmp = math_matrix * 2.5;\n";
    // tmp = math_matrix * 2.5;
    // std::cout << "Матрица после операции:\n";
    // std::cout << tmp << "\n\n";

    // Matrix<double> det_matrix = {{38, 382, 21, 9},
    //                              {21, 1, 9, 11},
    //                              {118, 5, 85, 2},
    //                              {10, 8, 22, 13}};
    // std::cout << "\ndet_matrix:\n"
    //           << det_matrix << "\n\n";

    // std::cout << "Операция: det_matrix.determinant();\n";
    // std::cout << "Результат: " << det_matrix.determinant() << "\n";

    // // std::cout << "Операция: det_matrix.inverse();\n";
    // // det_matrix.inverse();
    // std::cout << "Результат: \n"
    //           << det_matrix << "\n";

    // std::cout << "Матричное умножение: \n";
    // Matrix<double> res;
    // Matrix<double> m1 = {{1},
    //                      {2},
    //                      {3}},
    //                m2 = {{1, 2}};
    // std::cout << "Операция: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    // res = m1 * m2;
    // std::cout << "Результат:\n"
    //           << res << "\n\n";

    // std::cout << "Ошибки:\n\n";
    // std::cout << "Обращение к неверному индексу столбца:\n";
    // try
    // {
    //     res[0][100] = 1;
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n\n";
    // }

    // std::cout << "Обращение к неверному индексу строки:\n";
    // try
    // {
    //     res[100][0] = 22;
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n\n";
    // }

    // std::cout << "Сложение с неправильными матрицами:\n";
    // try
    // {
    //     Matrix<int> m1 = {{1, 2, 3}};
    //     Matrix<int> m2 = {{1, 2},
    //                       {3, 4}};
    //     std::cout << m1 + m2;
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n\n";
    // }

    // std::cout << "Умножение неправильных матриц:\n";
    // try
    // {
    //     Matrix<int> m1 = {{1, 2, 3}};
    //     Matrix<int> m2 = {{1, 2, 3}};
    //     std::cout << m1 * m2;
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n\n";
    // }

    // std::cout << "Вызов конструктора с неправильными аргументами:\n";
    // try
    // {
    //     Matrix<int> matrix_inv = {{1, 2},
    //                               {3}};
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n\n";
    // }

    // std::cout << "Вызов конструктора с нерабочей си матрицей\n";
    // try
    // {
    //     int **ec_matrix = NULL;
    //     Matrix<int> matr_er{2, 2, ec_matrix};
    //     std::cout << matr_er << "\n\n";
    // }
    // catch (MatrixExceptions &err)
    // {
    //     std::cout << err.what() << "\n\n";
    // }

    return 0;
}

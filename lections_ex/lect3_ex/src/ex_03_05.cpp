// Пример 03.05. Автоматическое выведение типа.

#include <iostream>

int main()
{
    int i = 0;
    const int ci = 0;
    int &lv = i;
    const int &clv = ci;
    int &&rv = i + 1;

    // тип int
    {
        // auto - компилятор на этапе компиляции должен определить тип 
        // переменной на основе типа инициализируемого выражения.
        auto x1 = i;
        auto x2 = ci;
        auto x3 = lv;
        auto x4 = clv;
        auto x5 = rv;
        auto x6 = i + 1;
    }

    // тип int&
    {
        auto &refx1 = i;
        auto &refx3 = lv;
        auto &refx5 = rv;
    }

    // тип const int&
    {
        auto &crefx2 = ci;
        auto &crefx4 = clv;
    }

    // тип const int&
    {
        const auto &crefx1 = i;
        const auto &crefx2 = ci;
        const auto &crefx3 = lv;
        const auto &crefx4 = clv;
        const auto &crefx5 = rv;
        const auto &crefx6 = i + 1;
    }

    // тип int&
    {
        auto &&refx1 = i;
        auto &&refx3 = lv;
        auto &&refx5 = rv;
    }

    // тип const int&
    {
        auto &&crefx2 = ci;
        auto &&crefx4 = clv;
    }

    // тип int&&
    {
        auto &&refx6 = i + 1;
    }
}
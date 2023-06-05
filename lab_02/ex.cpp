#include <iostream>

template <typename T>
concept size = sizeof(T) <= sizeof(int);

template <typename T>
    requires size<T> // в качестве ограничения применяется size
T sum(T a, T b)
{
    return a + b;
}

int main()
{
    std::cout << sum(10, 3) << std::endl; // 13
    // std::cout << sum(10.6, 3.7) << std::endl; // ! Ошибка
}
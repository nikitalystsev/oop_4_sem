// Пример 05.02. Создание и уничтожение объектов.

#include <iostream>

using namespace std;

class A
{
private:
    int value = 1;

public:
    A() { cout << "по умолчанию\n"; value *= 2; } // конструктор без параметров
    A(const A &) { cout << "копирование\n"; value *= 3; } // конструктор копирования
    A(A &&) // конструктор перемещения
    noexcept { cout << "перемещение\n"; value *= 4; }
    ~A() { cout << "деструктор " << value << endl; } // деструктор
};

A f(A obj) { return obj; }

A f1() { return A(); }

A f2()
{
    A obj;

    return obj;
}

int main()
{
    cout << "prim 1" << endl;
    {
        A obj;

        f(obj);
    }
    cout << "prim 2" << endl;
    {
        A obj = f1();
    }
    cout << "prim 3" << endl;
    {
        A obj = f2();
    }
}
// Пример 03.01. Ссылки lvalue и rvalue.
#include <iostream>

void f(int) {}

int main()
{
    int i = 0;

    int &lref1 = i;
    int &lref2(i);
    int &lref3{i};
    int &lref4 = {i};

    int &lv1 = i; // Ok!
    // int &lv2 = 2;           // Error!(не lvalue)
    // int &lv3 = i + 1;       // Error!(не lvalue)
    const int &lv4 = i + 1; // Ok!(создается объект)
    ++lv1;                  // Ok!

    // int &&rv1 = i;           // Error!(не rvalue)
    int &&rv2 = 2;           // Ok!
    int &&rv3 = i + 1;       // Ok!
    const int &&rv4 = i + 1; // Ok!
    ++rv2;                   // Ok!

    // int &&rv5 = rv2; // Error!(не rvalue)
    int &lv5 = rv2; // Ok!

    int &&rv6 = (int)i;       // Ok!( int(i) )
    int &&rv7 = std::move(i); // Ok!

    void (&reff)(int) = f;
    reff(1);
}

// Пример 06.02. Прямая и косвенная базы.

#include <iostream>

using namespace std;

class A
{
public:
    A(const char *s) { cout << "Creature A" << s << ";" << endl; }
};

class B : public A
{
public:
    B() : A(" from B") { cout << "Creature B;" << endl; }
};

class C : public B, public A
{
public:
    C() : A(" from C") { cout << "Creature C;" << endl; }
};

int main()
{
    C obj;

    return 0;
}
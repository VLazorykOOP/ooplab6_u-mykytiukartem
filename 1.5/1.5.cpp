#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ===== Ієрархія 1: Без віртуального успадкування =====
class A1 {
public:
    int a;
    A1() { cout << "A1 created\n"; }
    ~A1() { cout << "A1 destroyed\n"; }
};

class B1 {
public:
    int b;
    B1() { cout << "B1 created\n"; }
    ~B1() { cout << "B1 destroyed\n"; }
};

class C1 : public A1, public B1 {
public:
    int c;
    C1() { cout << "C1 created\n"; }
    ~C1() { cout << "C1 destroyed\n"; }
};

class D1 : public A1 {
public:
    int d;
    D1() { cout << "D1 created\n"; }
    ~D1() { cout << "D1 destroyed\n"; }
};

class E1 : public B1 {
public:
    int e;
    E1() { cout << "E1 created\n"; }
    ~E1() { cout << "E1 destroyed\n"; }
};

class F1 : public C1, public D1, public E1 {
public:
    int f;
    F1() { cout << "F1 created\n"; }
    ~F1() { cout << "F1 destroyed\n"; }
};

// ===== Ієрархія 2: З віртуальним успадкуванням =====
class A2 {
public:
    int a;
    A2() { cout << "A2 created\n"; }
    virtual ~A2() { cout << "A2 destroyed\n"; }
};

class B2 {
public:
    int b;
    B2() { cout << "B2 created\n"; }
    virtual ~B2() { cout << "B2 destroyed\n"; }
};

class C2 : virtual public A2, virtual public B2 {
public:
    int c;
    C2() { cout << "C2 created\n"; }
    virtual ~C2() { cout << "C2 destroyed\n"; }
};

class D2 : virtual public A2 {
public:
    int d;
    D2() { cout << "D2 created\n"; }
    virtual ~D2() { cout << "D2 destroyed\n"; }
};

class E2 : virtual public B2 {
public:
    int e;
    E2() { cout << "E2 created\n"; }
    virtual ~E2() { cout << "E2 destroyed\n"; }
};

class F2 : public C2, public D2, public E2 {
public:
    int f;
    F2() { cout << "F2 created\n"; }
    virtual ~F2() { cout << "F2 destroyed\n"; }
};

// ===== Введення даних =====
int inputValue(const string& source) {
    if (source == "random") {
        return rand() % 100;
    } else if (source == "keyboard") {
        int val;
        cout << "Введіть значення: ";
        cin >> val;
        return val;
    } else {
        ifstream file(source);
        int val;
        if (file >> val) return val;
        else return -1;
    }
}

// ===== Основна програма =====
int main() {
    srand(time(0));
    cout << "=== Створення F1 (без virtual inheritance) ===\n";
    F1 f1;
    cout << "=== Створення F2 (з virtual inheritance) ===\n";
    F2 f2;

    cout << "\n=== Розміри об'єктів ===\n";
    cout << "sizeof(A1): " << sizeof(A1) << endl;
    cout << "sizeof(B1): " << sizeof(B1) << endl;
    cout << "sizeof(C1): " << sizeof(C1) << endl;
    cout << "sizeof(D1): " << sizeof(D1) << endl;
    cout << "sizeof(E1): " << sizeof(E1) << endl;
    cout << "sizeof(F1): " << sizeof(F1) << endl;

    cout << "sizeof(A2): " << sizeof(A2) << endl;
    cout << "sizeof(B2): " << sizeof(B2) << endl;
    cout << "sizeof(C2): " << sizeof(C2) << endl;
    cout << "sizeof(D2): " << sizeof(D2) << endl;
    cout << "sizeof(E2): " << sizeof(E2) << endl;
    cout << "sizeof(F2): " << sizeof(F2) << endl;

    cout << "\n=== Тест введення значень ===\n";
    int r = inputValue("random");
    cout << "Random value: " << r << endl;

    int k = inputValue("keyboard");
    cout << "Keyboard value: " << k << endl;

    ofstream outFile("input.txt");
    outFile << 42;
    outFile.close();

    int f = inputValue("input.txt");
    cout << "From file: " << f << endl;

    return 0;
}

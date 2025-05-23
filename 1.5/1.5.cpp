#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class A {
protected:
    int a;
public:
    A() : a(rand() % 100) { cout << "A created\n"; }
    virtual ~A() { cout << "A destroyed\n"; }
    virtual void print() const { cout << "A: " << a << endl; }
};

class B {
protected:
    int b;
public:
    B() : b(rand() % 100) { cout << "B created\n"; }
    virtual ~B() { cout << "B destroyed\n"; }
    virtual void print() const { cout << "B: " << b << endl; }
};

// -------- Без віртуального успадкування --------
class C1 : public A, public B {
protected:
    int c;
public:
    C1() : c(rand() % 100) { cout << "C1 created\n"; }
    ~C1() override { cout << "C1 destroyed\n"; }
    void print() const override {
        A::print();
        B::print();
        cout << "C1: " << c << endl;
    }
};

class D1 : public C1 {
protected:
    int d;
public:
    D1() : d(rand() % 100) { cout << "D1 created\n"; }
    ~D1() override { cout << "D1 destroyed\n"; }
    void print() const override {
        C1::print();
        cout << "D1: " << d << endl;
    }
};

class E1 : public C1 {
protected:
    int e;
public:
    E1() : e(rand() % 100) { cout << "E1 created\n"; }
    ~E1() override { cout << "E1 destroyed\n"; }
    void print() const override {
        C1::print();
        cout << "E1: " << e << endl;
    }
};

class F1 : public D1, public E1 {
protected:
    int f;
public:
    F1() : f(rand() % 100) { cout << "F1 created\n"; }
    ~F1() override { cout << "F1 destroyed\n"; }
    void print() const {
        D1::print(); // двозначність!
        E1::print();
        cout << "F1: " << f << endl;
    }
};

// -------- З віртуальним успадкуванням --------
class AV {
protected:
    int a;
public:
    AV() : a(rand() % 100) { cout << "AV created\n"; }
    virtual ~AV() { cout << "AV destroyed\n"; }
    virtual void print() const { cout << "AV: " << a << endl; }
};

class BV {
protected:
    int b;
public:
    BV() : b(rand() % 100) { cout << "BV created\n"; }
    virtual ~BV() { cout << "BV destroyed\n"; }
    virtual void print() const { cout << "BV: " << b << endl; }
};

class CV : public virtual AV, public virtual BV {
protected:
    int c;
public:
    CV() : c(rand() % 100) { cout << "CV created\n"; }
    ~CV() override { cout << "CV destroyed\n"; }
    void print() const override {
        AV::print();
        BV::print();
        cout << "CV: " << c << endl;
    }
};

class DV : public virtual CV {
protected:
    int d;
public:
    DV() : d(rand() % 100) { cout << "DV created\n"; }
    ~DV() override { cout << "DV destroyed\n"; }
    void print() const override {
        CV::print();
        cout << "DV: " << d << endl;
    }
};

class EV : public virtual CV {
protected:
    int e;
public:
    EV() : e(rand() % 100) { cout << "EV created\n"; }
    ~EV() override { cout << "EV destroyed\n"; }
    void print() const override {
        CV::print();
        cout << "EV: " << e << endl;
    }
};

class FV : public DV, public EV {
protected:
    int f;
public:
    FV() : f(rand() % 100) { cout << "FV created\n"; }
    ~FV() override { cout << "FV destroyed\n"; }
    void print() const {
        DV::print();
        EV::print();
        cout << "FV: " << f << endl;
    }
};

// -------- Тестування --------
int main() {
    srand(time(0));

    cout << "\n--- F1 (без віртуального успадкування) ---\n";
    F1 f1;
    f1.print();
    cout << "Size F1: " << sizeof(f1) << " bytes\n";

    cout << "\n--- FV (з віртуальним успадкуванням) ---\n";
    FV fv;
    fv.print();
    cout << "Size FV: " << sizeof(fv) << " bytes\n";

    return 0;
}

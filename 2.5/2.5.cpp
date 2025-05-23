#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// ===========================
// Абстрактний базовий клас
// ===========================
class Progression {
protected:
    double a0; // Перший елемент прогресії
    double d;  // Крок або знаменник прогресії
public:
    // Конструктор
    Progression(double a0 = 0.0, double d = 1.0) : a0(a0), d(d) {
        cout << "[Progression] Створено об'єкт базового класу.\n";
    }

    // Віртуальний деструктор
    virtual ~Progression() {
        cout << "[Progression] Видалено об'єкт базового класу.\n";
    }

    // Чиста віртуальна функція — підрахунок суми прогресії
    virtual double sum(int n) const = 0;

    // Введення з клавіатури
    virtual void inputFromKeyboard() {
        cout << "Введіть a0 і d/r: ";
        cin >> a0 >> d;
    }

    // Введення з файлу
    virtual void inputFromFile(ifstream& in) {
        in >> a0 >> d;
    }

    // Генерація випадкових значень
    virtual void inputRandom() {
        a0 = (rand() % 2001 - 1000) / 100.0; // [-10.00; 10.00]
        d = (rand() % 2001 - 1000) / 100.0;
    }

    // Виведення інформації
    virtual void printInfo() const {
        cout << "a0 = " << a0 << ", d/r = " << d << "\n";
    }
};

// ===========================
// Арифметична прогресія
// ===========================
class ArithmeticProgression : public Progression {
public:
    // Конструктор
    ArithmeticProgression(double a0 = 0.0, double d = 1.0) : Progression(a0, d) {
        cout << "[ArithmeticProgression] Створено.\n";
    }

    // Деструктор
    ~ArithmeticProgression() override {
        cout << "[ArithmeticProgression] Знищено.\n";
    }

    // Обчислення суми n елементів
    double sum(int n) const override {
        double an = a0 + (n - 1) * d;
        return (n * (a0 + an)) / 2.0;
    }

    // Виведення інформації
    void printInfo() const override {
        cout << "Арифметична прогресія: a0 = " << a0 << ", d = " << d << "\n";
    }
};

// ===========================
// Геометрична прогресія
// ===========================
class GeometricProgression : public Progression {
public:
    // Конструктор
    GeometricProgression(double a0 = 1.0, double r = 2.0) : Progression(a0, r) {
        cout << "[GeometricProgression] Створено.\n";
    }

    // Деструктор
    ~GeometricProgression() override {
        cout << "[GeometricProgression] Знищено.\n";
    }

    // Обчислення суми n елементів
    double sum(int n) const override {
        if (d == 1) return a0 * n; // Уникнення ділення на 0
        return a0 * (1 - pow(d, n)) / (1 - d);
    }

    // Виведення інформації
    void printInfo() const override {
        cout << "Геометрична прогресія: a0 = " << a0 << ", r = " << d << "\n";
    }
};

// ===========================
// Головна функція
// ===========================
int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Ініціалізація генератора випадкових чисел

    cout << "\n=== Випадкові дані ===\n";
    ArithmeticProgression ap;
    ap.inputRandom();
    ap.printInfo();
    cout << "Сума перших 5 елементів: " << ap.sum(5) << "\n\n";

    GeometricProgression gp;
    gp.inputRandom();
    gp.printInfo();
    cout << "Сума перших 5 елементів: " << gp.sum(5) << "\n\n";

    cout << "\n=== Введення з клавіатури ===\n";
    ArithmeticProgression ap2;
    ap2.inputFromKeyboard();
    ap2.printInfo();
    cout << "Сума перших 3 елементів: " << ap2.sum(3) << "\n\n";

    cout << "\n=== Введення з файлу ===\n";
    ifstream fin("input.txt");
    if (fin) {
        GeometricProgression gp2;
        gp2.inputFromFile(fin);
        gp2.printInfo();
        cout << "Сума перших 4 елементів: " << gp2.sum(4) << "\n\n";
        fin.close();
    } else {
        cerr << "Не вдалося відкрити файл input.txt\n";
    }

    return 0;
}

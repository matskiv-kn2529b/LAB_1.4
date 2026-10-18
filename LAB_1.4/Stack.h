#pragma once
#ifndef STACK_H
#define STACK_H

#include <string>

// Клас, що реалізує стек на динамічному масиві.
// Ємність НЕ обмежена штучною константою: при заповненні масив
// автоматично збільшується (подвоюється), тож push() завжди успішний,
// доки вистачає пам'яті комп'ютера.
class Stack {
private:
    static const int DEFAULT_CAPACITY = 10; // Початкова ємність за замовчуванням
    int* data;       // динамічний масив елементів
    int count;       // кількість елементів у стеку
    int capacity;    // поточний розмір виділеного масиву

    void reallocate(int newCapacity); // зміна розміру масиву зі збереженням елементів

public:
    // Конструктори та деструктор
    Stack();
    explicit Stack(int cap);
    Stack(const Stack& other);              // конструктор копіювання
    Stack& operator=(const Stack& other);   // оператор присвоєння
    ~Stack();

    // Константні методи зчитування (геттери)
    int getCount() const;
    int getCapacity() const;
    int getElement(int index) const;

    // Методи запису (сеттери) з перевіркою коректності аргументів
    bool setCount(int value);
    bool setCapacity(int value);
    bool setElement(int index, int value);

    void Init(int cap = DEFAULT_CAPACITY);
    void Read();
    void Display() const;
    std::string toString() const;

    // Специфічні методи роботи зі стеком
    bool push(int value);
    bool pop(int& value);
    int pop();
    bool peek(int& value) const;
    int peek() const;
    bool isEmpty() const;
    void clear();
};

#endif // STACK_H

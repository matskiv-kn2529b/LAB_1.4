#include "Stack.h"
#include <iostream>
#include <sstream>
#include <climits>
#include <new>

// ---------- Приватний допоміжний метод ----------
void Stack::reallocate(int newCapacity) {
    int* newData = new int[newCapacity](); // нулі за замовчуванням
    for (int i = 0; i < count; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// ---------- Конструктори, деструктор ----------
Stack::Stack() : data(nullptr), count(0), capacity(0) {
    Init(DEFAULT_CAPACITY);
}

Stack::Stack(int cap) : data(nullptr), count(0), capacity(0) {
    Init(cap);
}

Stack::Stack(const Stack& other) : data(nullptr), count(0), capacity(0) {
    data = new int[other.capacity]();
    for (int i = 0; i < other.count; ++i) {
        data[i] = other.data[i];
    }
    count = other.count;
    capacity = other.capacity;
}

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        int* newData = new int[other.capacity]();
        for (int i = 0; i < other.count; ++i) {
            newData[i] = other.data[i];
        }
        delete[] data;
        data = newData;
        count = other.count;
        capacity = other.capacity;
    }
    return *this;
}

Stack::~Stack() {
    delete[] data;
}

// ---------- Геттери ----------
int Stack::getCount() const {
    return count;
}

int Stack::getCapacity() const {
    return capacity;
}

int Stack::getElement(int index) const {
    if (index >= 0 && index < count) {
        return data[index];
    }
    std::cerr << "[Помилка]: Індекс " << index << " поза межами діапазону!" << std::endl;
    return -1;
}

// ---------- Сеттери з контролем коректності ----------
bool Stack::setCount(int value) {
    if (value >= 0 && value <= capacity) {
        count = value;
        return true;
    }
    std::cerr << "[Помилка]: Некоректне значення кількості: " << value
        << " (допустимо від 0 до " << capacity << ")" << std::endl;
    return false;
}

bool Stack::setCapacity(int value) {
    // Ємність має бути додатною і не меншою за поточну кількість елементів,
    // щоб не втратити дані.
    if (value > 0 && value >= count) {
        if (value != capacity) {
            try {
                reallocate(value);
            }
            catch (const std::bad_alloc&) {
                std::cerr << "[Помилка]: Недостатньо пам'яті для ємності " << value << std::endl;
                return false;
            }
        }
        return true;
    }
    std::cerr << "[Помилка]: Некоректне значення ємності: " << value
        << " (допустимо додатне, не менше за кількість елементів " << count << ")" << std::endl;
    return false;
}

bool Stack::setElement(int index, int value) {
    if (index >= 0 && index < count) {
        data[index] = value;
        return true;
    }
    std::cerr << "[Помилка]: Некоректний індекс елемента: " << index << std::endl;
    return false;
}

// ---------- Init ----------
void Stack::Init(int cap) {
    if (cap <= 0) {
        std::cerr << "[Помилка]: Некоректна ємність " << cap
            << ". Використано значення за замовчуванням (" << DEFAULT_CAPACITY << ")." << std::endl;
        cap = DEFAULT_CAPACITY;
    }
    delete[] data;
    data = new int[cap]();
    capacity = cap;
    count = 0;
}

// ---------- Read ----------
void Stack::Read() {
    int n;
    std::cout << "Введіть кількість елементів для заповнення стека (n >= 0): ";
    std::cin >> n;

    while (std::cin.fail() || n < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некоректне значення. Введіть ціле число n >= 0: ";
        std::cin >> n;
    }

    clear();
    std::cout << "Введіть " << n << " цілих чисел (значень елементів):" << std::endl;
    for (int i = 0; i < n; ++i) {
        int val;
        std::cout << "Елемент [" << i + 1 << "]: ";
        std::cin >> val;
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Некоректне значення. Введіть ціле число: ";
            std::cin >> val;
        }
        push(val);
    }
}

// ---------- toString / Display ----------
std::string Stack::toString() const {
    std::stringstream ss;
    ss << "Stack (елементів: " << count << ", ємність масиву: " << capacity << "): [ ";
    for (int i = 0; i < count; ++i) {
        ss << data[i];
        if (i < count - 1) {
            ss << ", ";
        }
    }
    ss << " ] (вершина -> " << (count > 0 ? std::to_string(data[count - 1]) : "порожньо") << ")";
    return ss.str();
}

void Stack::Display() const {
    std::cout << toString() << std::endl;
}

// ---------- Операції стека ----------
bool Stack::push(int value) {
    if (count == capacity) {
        // Масив заповнений -- автоматично збільшуємо його вдвічі
        if (capacity == INT_MAX) {
            std::cerr << "[Помилка]: Досягнуто технічну межу розміру стека!" << std::endl;
            return false;
        }
        int newCap = (capacity > INT_MAX / 2) ? INT_MAX : capacity * 2;
        try {
            reallocate(newCap);
        }
        catch (const std::bad_alloc&) {
            std::cerr << "[Помилка]: Недостатньо пам'яті! Неможливо додати " << value << std::endl;
            return false;
        }
    }
    data[count] = value;
    count++;
    return true;
}

bool Stack::pop(int& value) {
    if (isEmpty()) {
        std::cerr << "[Помилка]: Стек порожній! Неможливо вилучити елемент." << std::endl;
        return false;
    }
    count--;
    value = data[count];
    data[count] = 0; // не залишаємо "сміття" за межами вершини
    return true;
}

int Stack::pop() {
    int val = -1;
    pop(val);
    return val;
}

bool Stack::peek(int& value) const {
    if (isEmpty()) {
        std::cerr << "[Помилка]: Стек порожній!" << std::endl;
        return false;
    }
    value = data[count - 1];
    return true;
}

int Stack::peek() const {
    int val = -1;
    peek(val);
    return val;
}

bool Stack::isEmpty() const {
    return count == 0;
}

void Stack::clear() {
    for (int i = 0; i < count; ++i) {
        data[i] = 0;
    }
    count = 0;
}

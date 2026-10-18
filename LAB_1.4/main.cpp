#include <iostream>
#include <vector>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Stack.h"
#include "TrainSorter.h"

// Безпечне зчитування цілого числа (повертає false, якщо введено не число)
static bool readInt(int& value) {
    std::cin >> value;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Демонстрація різних способів створення об'єктів та масивів об'єктів
void demonstrateObjectCreation() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "  ДЕМОНСТРАЦІЯ СПОСОБІВ СТВОРЕННЯ ОБ'ЄКТІВ І МАСИВІВ   " << std::endl;
    std::cout << "=======================================================\n" << std::endl;

    // 1. Статичний об'єкт
    std::cout << "1. Звичайний статичний об'єкт (Stack s1(10)):" << std::endl;
    Stack s1(10);
    s1.push(11);
    s1.push(22);
    s1.Display();

    // 2. Динамічний об'єкт
    std::cout << "\n2. Динамічний об'єкт через new (Stack* s2 = new Stack(5)):" << std::endl;
    Stack* s2 = new Stack(5);
    s2->push(100);
    s2->push(200);
    s2->Display();
    delete s2;

    // 3. Конструктор за замовчуванням
    std::cout << "\n3. Конструктор за замовчуванням (Stack s3):" << std::endl;
    Stack s3;
    s3.push(1);
    s3.Display();

    // 4. Конструктор копіювання та присвоєння
    std::cout << "\n4. Копіювання: Stack s4(s1) та s3 = s1:" << std::endl;
    Stack s4(s1);
    s4.push(33);
    std::cout << "s1: "; s1.Display();
    std::cout << "s4 (копія s1 + push(33)): "; s4.Display();
    s3 = s1;
    std::cout << "s3 після s3 = s1: "; s3.Display();

    // 5. Статичний масив об'єктів
    std::cout << "\n5. Статичний масив об'єктів (Stack stackArray[3]):" << std::endl;
    Stack stackArray[3];
    for (int i = 0; i < 3; ++i) {
        stackArray[i].Init(5);
        stackArray[i].push((i + 1) * 10);
        std::cout << "stackArray[" << i << "]: ";
        stackArray[i].Display();
    }

    // 6. Динамічний масив об'єктів
    std::cout << "\n6. Динамічний масив об'єктів (Stack* dynArray = new Stack[2]):" << std::endl;
    Stack* dynArray = new Stack[2];
    dynArray[0].push(777);
    dynArray[1].push(888);
    std::cout << "dynArray[0]: "; dynArray[0].Display();
    std::cout << "dynArray[1]: "; dynArray[1].Display();
    delete[] dynArray;

    // 7. Стек без обмеження розміру
    std::cout << "\n7. Стек не обмежений 100 елементами (push 1000 елементів у Stack(2)):" << std::endl;
    Stack big(2);
    for (int i = 1; i <= 1000; ++i) {
        big.push(i);
    }
    std::cout << "Кількість елементів: " << big.getCount()
        << ", ємність масиву автоматично зросла до " << big.getCapacity()
        << ", вершина: " << big.peek() << std::endl;

    std::cout << "\nДемонстрацію успішно завершено!\n" << std::endl;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    std::string sampleFileName = "train_data.txt";
    TrainSorter::createSampleFile(sampleFileName);

    Stack demoStack(15);
    int mainChoice = -1;

    while (mainChoice != 0) {
        std::cout << "\n=======================================================" << std::endl;
        std::cout << "         ГОЛОВНЕ МЕНЮ -- ЛАБОРАТОРНА РОБОТА N 1.4      " << std::endl;
        std::cout << "    Варіант 21: Клас Stack & Т-подібний сортувальний вузол" << std::endl;
        std::cout << "=======================================================" << std::endl;
        std::cout << " 1. Меню перевірки всіх методів класу Stack" << std::endl;
        std::cout << " 2. Демонстрація різних способів створення об'єктів" << std::endl;
        std::cout << " 3. Моделювання сортування потягу (введення з клавіатури)" << std::endl;
        std::cout << " 4. Моделювання сортування потягу (зчитування з файлу)" << std::endl;
        std::cout << " 0. Вихід з програми" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "Ваш вибір: ";

        if (!readInt(mainChoice)) {
            mainChoice = -1;
            std::cout << "Невірний пункт меню!" << std::endl;
            continue;
        }

        switch (mainChoice) {
        case 1: {
            int subChoice = -1;
            while (subChoice != 0) {
                std::cout << "\n--- МЕНЮ ТЕСТУВАННЯ МЕТОДІВ КЛАСУ STACK ---" << std::endl;
                std::cout << " 1. Push (додати елемент)" << std::endl;
                std::cout << " 2. Pop (вилучити елемент)" << std::endl;
                std::cout << " 3. Peek (вершина стека)" << std::endl;
                std::cout << " 4. Display / toString (вивести стан)" << std::endl;
                std::cout << " 5. Read (введення всієї структури з клавіатури)" << std::endl;
                std::cout << " 6. Init (ініціалізація/скидання)" << std::endl;
                std::cout << " 7. Перевірка Геттерів і Сеттерів" << std::endl;
                std::cout << " 8. Clear (очистити стек)" << std::endl;
                std::cout << " 9. Додати N елементів (перевірка зростання стека)" << std::endl;
                std::cout << " 0. Повернутися у головне меню" << std::endl;
                std::cout << "Вибір: ";

                if (!readInt(subChoice)) {
                    subChoice = -1;
                    std::cout << "Невірний пункт меню!" << std::endl;
                    continue;
                }

                if (subChoice == 1) {
                    int val;
                    std::cout << "Введіть число: ";
                    if (!readInt(val)) {
                        std::cout << "Помилка: потрібно ввести ціле число." << std::endl;
                    }
                    else if (demoStack.push(val)) {
                        std::cout << "Успішно додано " << val << std::endl;
                    }
                }
                else if (subChoice == 2) {
                    int val;
                    if (demoStack.pop(val)) {
                        std::cout << "Вилучено елемент: " << val << std::endl;
                    }
                }
                else if (subChoice == 3) {
                    int val;
                    if (demoStack.peek(val)) {
                        std::cout << "На вершині знаходиться: " << val << std::endl;
                    }
                }
                else if (subChoice == 4) {
                    std::cout << "Метод Display(): ";
                    demoStack.Display();
                    std::cout << "Метод toString(): " << demoStack.toString() << std::endl;
                }
                else if (subChoice == 5) {
                    demoStack.Read();
                }
                else if (subChoice == 6) {
                    int cap;
                    std::cout << "Введіть початкову ємність: ";
                    if (!readInt(cap)) {
                        std::cout << "Помилка: потрібно ввести ціле число." << std::endl;
                    }
                    else {
                        demoStack.Init(cap);
                        std::cout << "Стек ініціалізовано." << std::endl;
                    }
                }
                else if (subChoice == 7) {
                    std::cout << "getCount(): " << demoStack.getCount() << std::endl;
                    std::cout << "getCapacity(): " << demoStack.getCapacity() << std::endl;
                    std::cout << "\nТест некоректного setCount(-5): ";
                    demoStack.setCount(-5);
                    std::cout << "Тест некоректного setCapacity(-10): ";
                    demoStack.setCapacity(-10);
                    std::cout << "Тест коректного setCapacity(300): "
                        << (demoStack.setCapacity(300) ? "Успіх" : "Невдача") << std::endl;
                    std::cout << "getCapacity() після зміни: " << demoStack.getCapacity() << std::endl;
                    std::cout << "Тест некоректного getElement(1000): "
                        << demoStack.getElement(1000) << std::endl;
                    if (!demoStack.isEmpty()) {
                        std::cout << "Тест setElement(0, 555): "
                            << (demoStack.setElement(0, 555) ? "Успіх" : "Невдача") << std::endl;
                        std::cout << "getElement(0): " << demoStack.getElement(0) << std::endl;
                    }
                    else {
                        std::cout << "(Додайте елементи, щоб перевірити setElement/getElement.)" << std::endl;
                    }
                }
                else if (subChoice == 8) {
                    demoStack.clear();
                    std::cout << "Стек очищено." << std::endl;
                }
                else if (subChoice == 9) {
                    int n;
                    std::cout << "Скільки елементів додати? ";
                    if (!readInt(n) || n < 0) {
                        std::cout << "Помилка: потрібно ввести невід'ємне ціле число." << std::endl;
                    }
                    else {
                        for (int i = 1; i <= n; ++i) {
                            demoStack.push(i);
                        }
                        std::cout << "Додано " << n << " елементів. Кількість: " << demoStack.getCount()
                            << ", ємність масиву: " << demoStack.getCapacity() << std::endl;
                    }
                }
                else if (subChoice != 0) {
                    std::cout << "Невірний пункт меню!" << std::endl;
                }
            }
            break;
        }
        case 2:
            demonstrateObjectCreation();
            break;
        case 3: {
            std::cout << "\n--- Формування потягу з КЛАВІАТУРИ ---" << std::endl;
            std::vector<int> inputTrain = TrainSorter::readTrainFromKeyboard();
            TrainSorter::displayTrain("Початковий потяг", inputTrain);

            std::vector<int> track1, track2;
            Stack sortingStack; // стек сам зростає за потреби
            TrainSorter::sortTrain(inputTrain, track1, track2, sortingStack);

            TrainSorter::displayTrain("Сформований Потяг 1 (Напрямок 1, вагони типу 1)", track1);
            TrainSorter::displayTrain("Сформований Потяг 2 (Напрямок 2, вагони типу 2)", track2);
            break;
        }
        case 4: {
            std::cout << "\n--- Формування потягу з ФАЙЛУ ('" << sampleFileName << "') ---" << std::endl;
            std::vector<int> inputTrain = TrainSorter::readTrainFromFile(sampleFileName);

            if (inputTrain.empty()) {
                std::cout << "Не вдалося прочитати потяг або файл порожній." << std::endl;
            }
            else {
                TrainSorter::displayTrain("Початковий потяг з файлу", inputTrain);

                std::vector<int> track1, track2;
                Stack sortingStack;
                TrainSorter::sortTrain(inputTrain, track1, track2, sortingStack);

                TrainSorter::displayTrain("Сформований Потяг 1 (Напрямок 1, вагони типу 1)", track1);
                TrainSorter::displayTrain("Сформований Потяг 2 (Напрямок 2, вагони типу 2)", track2);
            }
            break;
        }
        case 0:
            std::cout << "Програму завершено!" << std::endl;
            break;
        default:
            std::cout << "Невірний пункт меню!" << std::endl;
            break;
        }
    }

    return 0;
}

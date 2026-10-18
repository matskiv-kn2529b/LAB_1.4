#include "TrainSorter.h"
#include <iostream>
#include <fstream>

// Принцип роботи Т-подібного вузла:
// Вхідна колія -> Т-подібний роздоріж та сортувальний тупик (Стек).
// Вагони типу 1 вирушають безпосередньо у Напрямок 1.
// Вагони типу 2 заштовхуються у сортувальний тупик (Стек).
// Після проходження вхідного потягу вагони типу 2 з тупика (Стека) виштовхуються у Напрямок 2.
void TrainSorter::sortTrain(const std::vector<int>& inputTrain,
    std::vector<int>& track1,
    std::vector<int>& track2,
    Stack& sortingStack) {
    track1.clear();
    track2.clear();
    sortingStack.clear();

    std::cout << "\n=== КРОК ЗА КРОКОМ: СОРТУВАННЯ НА Т-ПОДІБНОМУ ВУЗЛІ ===" << std::endl;

    for (size_t i = 0; i < inputTrain.size(); ++i) {
        int wagon = inputTrain[i];
        std::cout << "Вагон #" << (i + 1) << " (Тип " << wagon << ") -> ";

        if (wagon == 1) {
            std::cout << "направляється прямо у Напрямок 1 (Колія 1)." << std::endl;
            track1.push_back(wagon);
        }
        else if (wagon == 2) {
            std::cout << "заштовхується у сортувальний тупик (Push у Стек)." << std::endl;
            if (!sortingStack.push(wagon)) {
                std::cout << "[УВАГА]: Не вдалося додати вагон у тупик (немає пам'яті)!" << std::endl;
            }
        }
        else {
            std::cout << "Невідомий тип вагона! Пропущено." << std::endl;
        }
    }

    std::cout << "\nВивантаження вагонів із тупика (Pop зі Стека) у Напрямок 2 (Колія 2)..." << std::endl;
    while (!sortingStack.isEmpty()) {
        int wagon = sortingStack.pop();
        track2.push_back(wagon);
        std::cout << "Вагон (Тип " << wagon << ") виштовхнуто з тупика у Напрямок 2." << std::endl;
    }
    std::cout << "=== СОРТУВАННЯ ЗАВЕРШЕНО ===\n" << std::endl;
}

std::vector<int> TrainSorter::readTrainFromKeyboard() {
    std::vector<int> train;
    int count;
    std::cout << "Введіть загальну кількість вагонів у потязі: ";
    std::cin >> count;

    while (std::cin.fail() || count <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Помилка! Введіть додатне число вагонів: ";
        std::cin >> count;
    }

    std::cout << "Введіть типи вагонів (1 або 2) послідовно:" << std::endl;
    for (int i = 0; i < count; ++i) {
        int type = 0;
        while (true) {
            std::cout << "Вагон " << (i + 1) << " (введіть 1 або 2): ";
            std::cin >> type;
            if (std::cin.fail()) {
                // не число -- очищаємо потік, інакше цикл став би нескінченним
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Помилка! Введіть число 1 або 2." << std::endl;
            }
            else if (type != 1 && type != 2) {
                std::cout << "Помилка! Допустимі лише типи 1 та 2." << std::endl;
            }
            else {
                break;
            }
        }
        train.push_back(type);
    }
    return train;
}

std::vector<int> TrainSorter::readTrainFromFile(const std::string& filename) {
    std::vector<int> train;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[Помилка]: Не вдалося відкрити файл '" << filename << "'!" << std::endl;
        return train;
    }

    int type;
    while (file >> type) {
        if (type == 1 || type == 2) {
            train.push_back(type);
        }
        else {
            std::cerr << "[Увага]: у файлі знайдено недопустимий тип вагона " << type
                << " -- пропущено." << std::endl;
        }
    }
    if (!file.eof()) {
        std::cerr << "[Увага]: у файлі знайдено нечислові дані -- подальше читання зупинено." << std::endl;
    }
    file.close();
    return train;
}

bool TrainSorter::createSampleFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    // Записуємо послідовність типів вагонів через пробіл
    file << "1 2 1 1 2 2 1 2 1 2\n";
    file.close();
    return true;
}

void TrainSorter::displayTrain(const std::string& label, const std::vector<int>& train) {
    std::cout << label << " [кількість: " << train.size() << "]: ";
    if (train.empty()) {
        std::cout << "(порожньо)";
    }
    else {
        std::cout << "[ ";
        for (size_t i = 0; i < train.size(); ++i) {
            std::cout << train[i] << (i < train.size() - 1 ? ", " : "");
        }
        std::cout << " ]";
    }
    std::cout << std::endl;
}

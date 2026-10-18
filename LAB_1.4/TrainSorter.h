#pragma once
#ifndef TRAIN_SORTER_H
#define TRAIN_SORTER_H

#include <vector>
#include <string>
#include "Stack.h"

// Модуль для моделювання Т-подібного сортувального вузла залізниці
class TrainSorter {
public:
    // Моделювання розділення потягу на два напрямки за допомогою стека-тупика
    static void sortTrain(const std::vector<int>& inputTrain,
        std::vector<int>& track1,
        std::vector<int>& track2,
        Stack& sortingStack);

    // Введення складу потягу з клавіатури
    static std::vector<int> readTrainFromKeyboard();

    // Зчитування складу потягу з файлу
    static std::vector<int> readTrainFromFile(const std::string& filename);

    // Допоміжний метод: створює приклад файлу з потягом
    static bool createSampleFile(const std::string& filename);

    // Виведення складу
    static void displayTrain(const std::string& label, const std::vector<int>& train);
};

#endif

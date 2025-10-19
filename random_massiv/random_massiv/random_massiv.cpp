#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

int main() {
    // Размеры массивов
    std::vector<int> sizes = { 10000, 100000, 1000000 };
    // Диапазоны значений (min, max)
    std::vector<std::pair<int, int>> ranges = {
        {-10, 10},
        {-1000, 1000},
        {-100000, 100000}
    };

    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int size : sizes) {
        for (auto range : ranges) {
            int low = range.first;
            int high = range.second;

            // Имя файла
            std::string filename = "array_" + std::to_string(size) + "_" +
                std::to_string(low) + "_" +
                std::to_string(high) + ".txt";

            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка при открытии файла " << filename << std::endl;
                continue;
            }

            // Настройка распределения
            std::uniform_int_distribution<> dist(low, high);

            // Генерация и запись чисел
            for (int i = 0; i < size; ++i) {
                file << dist(gen);
                if (i < size - 1) file << " ";
            }

            file.close();
            std::cout << "Создан файл: " << filename << std::endl;
        }
    }

    std::cout << "Готово!" << std::endl;
    return 0;
}

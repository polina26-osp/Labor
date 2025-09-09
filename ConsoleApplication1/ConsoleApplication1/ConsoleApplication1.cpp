#include <random>
#include <iostream>
#include <chrono>

int main()
{
    std::random_device randomDevice;
    std::mt19937_64 generator(randomDevice());

    int rangeStart, rangeEnd;

    std::cin >> rangeStart >> rangeEnd;

    std::uniform_int_distribution<int> distribution(rangeStart, rangeEnd);

    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();

    int numValues;
    std::cin >> numValues;

    for (int i = 0; i < numValues; i++)
    {
        std::cout << distribution(generator) << ' ';
    }

    std::cout << std::endl;

    std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = timeEnd - timeStart;

    std::cout << duration.count() << std::endl;

    return 0;
}
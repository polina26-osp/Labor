#include <stdio.h>
#include <locale.h>  

int main() {
    setlocale(LC_ALL, "Rus");
    const char* filenames[] = {
        "array_10000_-10_10.txt",
        "array_10000_-1000_1000.txt",
        "array_10000_-100000_100000.txt",
        "array_100000_-10_10.txt",
        "array_100000_-1000_1000.txt",
        "array_100000_-100000_100000.txt"
    };
    int num_files = sizeof(filenames) / sizeof(filenames[0]);

    for (int i = 0; i < num_files; ++i) {
        FILE* file = NULL;
        errno_t err = fopen_s(&file, filenames[i], "rt");
        if (err != 0 || file == NULL) {
            printf("Ошибка: не удалось открыть файл \n");
        }
        else {
            printf("Файл успешно открыт \n");
            fclose(file);
        }
    }
    return 0;
}
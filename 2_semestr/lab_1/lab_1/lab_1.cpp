#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Проверка, пуст ли файл
int isFileEmpty(const char* filename) {
    FILE* f = NULL;
    errno_t err = fopen_s(&f, filename, "rt");
    if (err != 0 || f == NULL) return 1;
    int dummy;
    int res = fscanf_s(f, "%d", &dummy);
    fclose(f);
    return res != 1;
}

// Копирование файла 
void copyFile(const char* src, const char* dst) {
    FILE* in = NULL;
    FILE* out = NULL;
    errno_t err_in = fopen_s(&in, src, "rt");
    errno_t err_out = fopen_s(&out, dst, "wt");
    if (err_in != 0 || in == NULL || err_out != 0 || out == NULL) {
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch, out);
    }
    fclose(in);
    fclose(out);
}

// Исходный файл f разбивается на fa и fb сериями длины p
void distribute(const char* f, const char* fa, const char* fb, int p) {
    FILE* src = NULL;
    FILE* dst1 = NULL;
    FILE* dst2 = NULL;
    errno_t err_src = fopen_s(&src, f, "rt");
    errno_t err_dst1 = fopen_s(&dst1, fa, "wt");
    errno_t err_dst2 = fopen_s(&dst2, fb, "wt");
    if (err_src != 0 || src == NULL || err_dst1 != 0 || dst1 == NULL || err_dst2 != 0 || dst2 == NULL) {
        if (src) fclose(src);
        if (dst1) fclose(dst1);
        if (dst2) fclose(dst2);
        return;
    }

    int turn = 0;      // 0 - записываем в fa, 1 - в fb
    int count = 0;
    int value;
    while (fscanf_s(src, "%d", &value) == 1) {
        if (turn == 0)
            fprintf(dst1, "%d ", value);
        else
            fprintf(dst2, "%d ", value);

        ++count;
        if (count == p) {
            turn = 1 - turn;
            count = 0;
        }
    }

    fclose(src);
    fclose(dst1);
    fclose(dst2);
}

// Слияние из двух файлов-источников в два файла-приёмника с чередованием
void merge() {
    
}

// Функция сортировки прямым слиянием на 4-ех файла
void sortFile(const char* inputFilename) {
    const char* fa = "fa.tmp";
    const char* fb = "fb.tmp";
    const char* fc = "fc.tmp";
    const char* fd = "fd.tmp";

    int p = 1;

    // Разбиение исходного файла на fa и fb
    distribute(inputFilename, fa, fb, p);

    while (1) {
        // Слияние из fa, fb в fc, fd
        

        // Слияние из fc, fd в fa, fb
        
    }

    // Удаление временных файлов
    remove(fa); remove(fb); remove(fc); remove(fd);
}

// Проверка файла на упорядоченность
int isFileContainsSortedArray(const char* fileName) {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, fileName, "rt");
    if (err != 0 || file == NULL) {
        printf("Error: couldn't read from file in function 'isFileContainsSortedArray'.\n");
        return -1;
    }

    int value1 = 0, value2 = 0;

    // Пытаемся прочитать первое число
    if (fscanf_s(file, "%d", &value1) != 1) {
        fclose(file);
        return 1;  // Пустой файл считаем упорядоченным
    }

    // Читаем остальные числа и проверяем порядок
    while (fscanf_s(file, "%d", &value2) == 1) {
        if (value1 > value2) {
            fclose(file);
            return 0;
        }
        value1 = value2;
    }

    fclose(file);
    return 1;
}

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
        printf("Обработка файла %s...\n", filenames[i]);

        // Проверяем, существует ли файл и можно ли его открыть
        FILE* file = NULL;
        errno_t err = fopen_s(&file, filenames[i], "rt");
        if (err != 0 || file == NULL) {
            printf("  Ошибка: не удалось открыть файл \n");
            continue;
        }
        fclose(file);

        // Сортируем файл 
        sortFile(filenames[i]);

        // Проверка на отсортированность
        int result = isFileContainsSortedArray(filenames[i]);
        if (result == 1) {
            printf("  Файл отсортирован.\n");
        }
        else if (result == 0) {
            printf("  Ошибка: файл не отсортирован \n");
        }
        else {
            printf("  Ошибка при проверке файла.\n");
        }
        printf("\n");
    }

    return 0;
}
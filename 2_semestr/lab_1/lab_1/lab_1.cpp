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
    FILE* dst[2] = { NULL, NULL };
    errno_t err_src = fopen_s(&src, f, "rt");
    errno_t err_dst[2];
    err_dst[0] = fopen_s(&dst[0], fa, "wt");
    err_dst[1] = fopen_s(&dst[1], fb, "wt");

    if (err_src != 0 || src == NULL ||
        err_dst[0] != 0 || dst[0] == NULL ||
        err_dst[1] != 0 || dst[1] == NULL) {
        if (src) fclose(src);
        if (dst[0]) fclose(dst[0]);
        if (dst[1]) fclose(dst[1]);
        return;
    }

    int turn = 0;      // 0 - записываем в fa (dst1), 1 - в fb (dst2)
    int count = 0;     // число элементов в текущей серии
    int value;
    while (fscanf_s(src, "%d", &value) == 1) {
        fprintf(dst[turn], "%d ", value);


        ++count;
        if (count == p) {
            turn = 1 - turn;
            count = 0;
        }
    }

    fclose(src);
    fclose(dst[0]);
    fclose(dst[1]);
}

// Слияние из двух файлов-источников в два файла-приёмника с чередованием
// src1, src2 (f1, f2) - исходные файлы
// dst1, dst2 (out1, out2) - выходные файлы 
// p - длина серии
void merge(const char* src1, const char* src2,
    const char* dst1, const char* dst2, int p) {
    FILE* f[2] = { NULL, NULL };
    FILE* out[2] = { NULL, NULL };
    errno_t err_f1 = fopen_s(&f[0], src1, "rt");
    errno_t err_f2 = fopen_s(&f[1], src2, "rt");
    errno_t err_out1 = fopen_s(&out[0], dst1, "wt");
    errno_t err_out2 = fopen_s(&out[1], dst2, "wt");
    if (err_f1 != 0 || f[0] == NULL || err_f2 != 0 || f[1] == NULL ||
        err_out1 != 0 || out[0] == NULL || err_out2 != 0 || out[1] == NULL) {
        if (f[0]) fclose(f[0]);
        if (f[1]) fclose(f[1]);
        if (out[0]) fclose(out[0]);
        if (out[1]) fclose(out[1]);
        return;
    }

    int turn = 0;               // 0 - в out[0], 1 - в out[1]
    int eof[2] = { 0, 0 };     // флаги конца файла, 1 - файл закончился
    int val[2];             // текущие значения файлов
    int has[2] = { 0, 0 };     // есть ли еще элементы в текущей серии
    int remaining[2] = { 0, 0 };     // сколько элементов осталось в текущей серии

    while (1) {
        // Попытка начать новую серию из первого файла
        if (!eof[0] && remaining[0] == 0) {
            remaining[0] = p;
            if (fscanf_s(f[0], "%d", &val[0]) == 1) {
                has[0] = 1;
                --remaining[0];
            }
            else {
                eof[0] = 1;
                remaining[0] = 0;
                has[0] = 0;
            }
        }
        // Попытка начать новую серию из второго файла
        if (!eof[1] && remaining[1] == 0) {
            remaining[1] = p;
            if (fscanf_s(f[1], "%d", &val[1]) == 1) {
                has[1] = 1;
                --remaining[1];
            }
            else {
                eof[1] = 1;
                remaining[1] = 0;
                has[1] = 0;
            }
        }

        // Если оба файла закончились – выход
        if (eof[0] && eof[1]) break;

        // Чередования файлов для записи
        FILE* currentOut = out[turn];

        // Слияние двух текущих серий 
        while (has[0] || has[1]) {
            if (has[0] && has[1]) {
                if (val[0] <= val[1]) {
                    fprintf(currentOut, "%d ", val[0]);
                    // Чтение следующего элемента из первого файла
                    if (remaining[0] > 0) {
                        if (fscanf_s(f[0], "%d", &val[0]) == 1) {
                            --remaining[0];
                        }
                        else {
                            has[0] = 0;
                            eof[0] = 1;
                        }
                    }
                    else {
                        has[0] = 0;
                    }
                }
                else {
                    fprintf(currentOut, "%d ", val[1]);
                    if (remaining[1] > 0) {
                        if (fscanf_s(f[1], "%d", &val[1]) == 1) {
                            --remaining[1];
                        }
                        else {
                            has[1] = 0;
                            eof[1] = 1;
                        }
                    }
                    else {
                        has[1] = 0;
                    }
                }
            }
            else if (has[0]) {
                fprintf(currentOut, "%d ", val[0]);
                if (remaining[0] > 0) {
                    if (fscanf_s(f[0], "%d", &val[0]) == 1) {
                        --remaining[0];
                    }
                    else {
                        has[0] = 0;
                        eof[0] = 1;
                    }
                }
                else {
                    has[0] = 0;
                }
            }
            else if (has[1]) {
                fprintf(currentOut, "%d ", val[1]);
                if (remaining[1] > 0) {
                    if (fscanf_s(f[1], "%d", &val[1]) == 1) {
                        --remaining[1];
                    }
                    else {
                        has[1] = 0;
                        eof[1] = 1;
                    }
                }
                else {
                    has[1] = 0;
                }
            }
        }
        turn = 1 - turn;
    }

    fclose(f[0]);
    fclose(f[1]);
    fclose(out[0]);
    fclose(out[1]);
}

// Функция сортировки прямым слиянием на 4-ех файла
void sortFile(const char* inputFilename) {
    const char* fa = "fa.tmp";
    const char* fb = "fb.tmp";
    const char* fc = "fc.tmp";
    const char* fd = "fd.tmp";

    int p = 1;
    int phase = 0;

    // Разбиение исходного файла на fa и fb
    distribute(inputFilename, fa, fb, p);

    while (1) {
        const char* src1 = (phase == 0) ? fa : fc;
        const char* src2 = (phase == 0) ? fb : fd;
        const char* dst1 = (phase == 0) ? fc : fa;
        const char* dst2 = (phase == 0) ? fd : fb;

        merge(src1, src2, dst1, dst2, p);

        const char* result = NULL;
        if (phase == 0) {
            if (isFileEmpty(fc) || isFileEmpty(fd)) {
                result = isFileEmpty(fc) ? fd : fc;
            }
        }
        else {
            if (isFileEmpty(fa) || isFileEmpty(fb)) {
                result = isFileEmpty(fa) ? fb : fa;
            }
        }

        if (result != NULL) {
            copyFile(result, inputFilename);
            break;
        }

        p *= 2;
        phase = 1 - phase;
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
    int num_files = sizeof(filenames) / sizeof(filenames[0]);   // к-во файлов 

    for (int i = 0; i < num_files; ++i) {
        printf("Обработка файла %s \n", filenames[i]);

        // Проверяем, существует ли файл и можно ли его открыть
        FILE* file = NULL;
        errno_t err = fopen_s(&file, filenames[i], "rt");
        if (err != 0 || file == NULL) {
            printf("Ошибка: не удалось открыть файл \n");
            continue;
        }
        fclose(file);

        // Сортируем файл 
        sortFile(filenames[i]);

        // Проверка на отсортированность
        int result = isFileContainsSortedArray(filenames[i]);
        if (result == 1) {
            printf("Файл отсортирован.\n");
        }
        else if (result == 0) {
            printf("Ошибка: файл не отсортирован \n");
        }
        else {
            printf("Ошибка при проверке файла.\n");
        }
        printf("\n");
    }

    return 0;
}

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

    int turn = 0;      // 0 - записываем в fa (dst1), 1 - в fb (dst2)
    int count = 0;     // число элементов в текущей серии
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
// src1, src2 (f1, f2) - исходные файлы
// dst1, dst2 (out1, out2) - выходные файлы 
// p - длина серии
void merge(const char* src1, const char* src2,
    const char* dst1, const char* dst2, int p) {
    FILE* f1 = NULL;
    FILE* f2 = NULL;
    FILE* out1 = NULL;
    FILE* out2 = NULL;
    errno_t err_f1 = fopen_s(&f1, src1, "rt");
    errno_t err_f2 = fopen_s(&f2, src2, "rt");
    errno_t err_out1 = fopen_s(&out1, dst1, "wt");
    errno_t err_out2 = fopen_s(&out2, dst2, "wt");
    if (err_f1 != 0 || f1 == NULL || err_f2 != 0 || f2 == NULL ||
        err_out1 != 0 || out1 == NULL || err_out2 != 0 || out2 == NULL) {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (out1) fclose(out1);
        if (out2) fclose(out2);
        return;
    }

    int turn = 0;               // 0 - в out1, 1 - в out2
    int eof1 = 0, eof2 = 0;     // флаги конца файла, 1 - файл закончился
    int val1, val2;             // текущие значения файлов
    int has1 = 0, has2 = 0;     // есть ли еще элементы в текущей серии
    int remaining1 = 0, remaining2 = 0;     // сколько элементов осталось в текущей серии

    while (1) {
        // Попытка начать новую серию из первого файла
        if (!eof1 && remaining1 == 0) {     //выполняется если файл еще не закончился и серия полностью обработана
            remaining1 = p;
            if (fscanf_s(f1, "%d", &val1) == 1) {
                has1 = 1;
                --remaining1;
            }
            else {
                eof1 = 1;      // файл 1 закончился
                remaining1 = 0;
                has1 = 0;
            }
        }
        // Попытка начать новую серию из второго файла
        if (!eof2 && remaining2 == 0) {
            remaining2 = p;
            if (fscanf_s(f2, "%d", &val2) == 1) {
                has2 = 1;
                --remaining2;
            }
            else {
                eof2 = 1;   // файл 2 закончился
                remaining2 = 0;
                has2 = 0;
            }
        }

        // Если оба файла закончились – выход
        if (eof1 && eof2) break;

        // Чередования файлов для записи
        FILE* out = (turn == 0) ? out1 : out2;

        // Слияние двух текущих серий 
        while (has1 || has2) {
            if (has1 && has2) {
                if (val1 <= val2) {
                    fprintf(out, "%d ", val1);
                    // Чтение следующего элемента из первого файла
                    if (remaining1 > 0) {
                        if (fscanf_s(f1, "%d", &val1) == 1) {
                            --remaining1;
                        }
                        else {
                            has1 = 0;   // серия 1 закончилась
                            eof1 = 1;   // файл закончился
                        }
                    }
                    else {
                        has1 = 0;   // серия 1 закончилась
                    }
                }
                else {
                    fprintf(out, "%d ", val2);
                    if (remaining2 > 0) {
                        if (fscanf_s(f2, "%d", &val2) == 1) {
                            --remaining2;
                        }
                        else {
                            has2 = 0;
                            eof2 = 1;
                        }
                    }
                    else {
                        has2 = 0;
                    }
                }
            }
            else if (has1) {        // только в 1 файле есть элементы
                fprintf(out, "%d ", val1);
                if (remaining1 > 0) {
                    if (fscanf_s(f1, "%d", &val1) == 1) {
                        --remaining1;
                    }
                    else {
                        has1 = 0;
                        eof1 = 1;
                    }
                }
                else {
                    has1 = 0;
                }
            }
            else if (has2) {        // только во 2 файле есть элементы
                fprintf(out, "%d ", val2);
                if (remaining2 > 0) {
                    if (fscanf_s(f2, "%d", &val2) == 1) {
                        --remaining2;
                    }
                    else {
                        has2 = 0;
                        eof2 = 1;
                    }
                }
                else {
                    has2 = 0;
                }
            }
        }
        turn = 1 - turn;        // две серии слиты, переключаемся на другой выходной файл
    }

    fclose(f1);
    fclose(f2);
    fclose(out1);
    fclose(out2);
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
        merge(fa, fb, fc, fd, p);
        if (isFileEmpty(fc) || isFileEmpty(fd)) {       // Если один из выходных файлов пуст - сортировка завершена
            const char* result = isFileEmpty(fc) ? fd : fc;
            copyFile(result, inputFilename);
            break;
        }
        p *= 2;     // увеличение размера серии

        // Слияние из fc, fd в fa, fb
        merge(fc, fd, fa, fb, p);
        if (isFileEmpty(fa) || isFileEmpty(fb)) {
            const char* result = isFileEmpty(fa) ? fb : fa;
            copyFile(result, inputFilename);
            break;
        }
        p *= 2;
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
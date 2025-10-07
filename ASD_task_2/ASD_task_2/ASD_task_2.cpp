#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

// Функция формирования таблицы сдвигов
vector<int> CreateTAB(const string& p) {
    int m = p.length();
    vector<int> t(256, m);
    for (int i = 0; i < m - 1; i++) {
        t[p[i]] = m - 1 - i;
    }
    return t;
}

// Функция поиска первого вхождения подстроки
int BMsearchFirst(const string& s, const string& p) {
    int n = s.length();
    int m = p.length();

    vector<int> t = CreateTAB(p);
    int i = m - 1;

    while (i < n) {
        int j = m - 1;
        int k = i;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) return k + 1;
        i += t[s[i]];
    }
    return -1;
}

// Функция поиска всех вхождений подстроки
vector<int> BMsearch(const string& s, const string& p) {
    vector<int> result;
    int n = s.length();
    int m = p.length();
    if (m == 0) return result;

    vector<int> t = CreateTAB(p);
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;
        int k = i + j;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) {
            result.push_back(i);
            i += 1;
        }
        else {
            i += t[s[i + m - 1]];
        }
    }
    return result;
}

// Функция поиска вхождений подстроки в заданном диапазоне
vector<int> BMsearchAllRange(const string& s, const string& p, int first, int last) {
    vector<int> result;
    int n = last + 1;
    int m = p.length();
    if (m == 0 || first > last) return result;

    vector<int> t = CreateTAB(p);
    int i = first + m - 1;

    while (i <= n - 1) {
        int j = m - 1;
        int k = i;
        while (j >= 0 && s[k] == p[j]) {
            k--;
            j--;
        }
        if (j < 0) {
            result.push_back(k + 1);
            i = k + 1 + m;
        }
        else {
            i += t[s[i]];
        }
    }
    return result;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int firstRange, lastRange;
    string t = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    string s = "tor";

    int first_i = BMsearchFirst(t, s);
    cout << "Первое вхождение: " << first_i << "\n";

    vector<int> all_i = BMsearch(t, s);
    cout << "Все вхождения: [ ";
    for (int ind = 0; ind < all_i.size(); ind++) cout << all_i[ind] << " ";
    cout << "]" << endl;

    cout << "Введите начало диапазона (начиная с 0): ";
    cin >> firstRange;
    
    if (firstRange < 0)
    {
        cerr << endl << "Ошибка: некорректный ввод первой границы";
        return -1;
    }

    cout << "Введите конец диапазона (до " << t.size() - 1 << "): ";
    cin >> lastRange;

    if (firstRange > lastRange || lastRange >= t.size())
    {
        cerr << endl << "Ошибка: некорректный ввод второй границы";
        return -1;
    }

    vector<int> range_i = BMsearchAllRange(t, s, firstRange, lastRange);
    cout << "Вхождения в заданном диапазоне: [ ";
    for (int ind = 0; ind < range_i.size(); ind++) cout << range_i[ind] << " ";
    cout << "]" << endl;

    return 0;
}

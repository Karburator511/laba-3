#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <locale>

using namespace std;

double F(double x, double a, double b, double c) {
    if (x < 0 && b != 0)
        return a * x * x + b;
    else if (x > 0 && b == 0)
        return (x - a) / (x - c);
    else
        return x / c;
}

void printArray(const vector<double>& arr, bool isHuman) {
    if (isHuman) {
        for (size_t i = 0; i < arr.size(); ++i) {
            cout << fixed << setprecision(2) << arr[i];
            if (i != arr.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    else {
        for (size_t i = 0; i < arr.size(); ++i) {
            cout << fixed << setprecision(2) << arr[i];
            if (i != arr.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void printHumanTable(const vector<double>& arr, double x1, double step, bool isFirstArray) {
    cout << "___|__________" << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        double x = isFirstArray ? (x1 + i * step) : -(x1 + i * step);
        cout << setw(3) << right << x << " | " << setw(8) << fixed << setprecision(2) << arr[i] << endl;
    }
    cout << "___|__________" << endl;
}

int main(int argc, char* argv[]) {
    // Настраиваем локализацию на русскую
    setlocale(LC_ALL, "ru_RU.UTF-8");

    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }

    double x1, x2, a, b, c;
    if (isHuman) {
        cout << "Введите значения x1, x2, a, b, c через пробел: ";
    }
    cin >> x1 >> x2 >> a >> b >> c;

    vector<double> firstArray(15), secondArray(15);
    double step = (x2 - x1) / 14;

    for (int i = 0; i < 15; ++i) {
        double x = x1 + i * step;
        firstArray[i] = F(x, a, b, c);
        secondArray[i] = F(-x, a, b, c);
    }

    for (int i = 0; i < 15; ++i) {
        int a_int = static_cast<int>(a);
        int b_int = static_cast<int>(b);
        int c_int = static_cast<int>(c);
        if ((a_int | b_int) & (a_int | c_int) == 0) {
            firstArray[i] = round(firstArray[i]);
            secondArray[i] = round(secondArray[i]);
        }
    }

    if (isHuman) {
        cout << "Таблица значений для первого массива:" << endl;
        printHumanTable(firstArray, x1, step, true);
        cout << "Таблица значений для второго массива:" << endl;
        printHumanTable(secondArray, x1, step, false);
    }
    else {
        printArray(firstArray, isHuman);
        printArray(secondArray, isHuman);
    }

    for (int i = 0; i < 3; ++i) {
        double minimum = *min_element(firstArray.begin() + 5 * i, firstArray.begin() + 5 * (i + 1));
        cout << fixed << setprecision(2) << minimum << endl;
    }

    vector<double> sortedArray = firstArray;
    sort(sortedArray.begin(), sortedArray.end());
    printArray(sortedArray, isHuman);

    int duplicateCount = 0;
    for (int i = 1; i < 15; ++i) {
        if (sortedArray[i] == sortedArray[i - 1]) {
            duplicateCount++;
        }
    }
    cout << duplicateCount << endl;

    int powerOfTwoIndex = -1;
    for (int i = 0; i < 15 - 5; ++i) {
        if (firstArray[i] == 1) {
            bool isSequence = true;
            for (int j = 1; j < 5; ++j) {
                if (firstArray[i + j] != pow(2, j)) {
                    isSequence = false;
                    break;
                }
            }
            if (isSequence) {
                powerOfTwoIndex = i;
                break;
            }
        }
    }
    cout << powerOfTwoIndex << endl;

    vector<double> negativeArray, positiveArray;
    for (double val : firstArray) {
        if (val < 0)
            negativeArray.push_back(val);
        else if (val > 0)
            positiveArray.push_back(val);
    }
    for (double val : secondArray) {
        if (val < 0)
            negativeArray.push_back(val);
        else if (val > 0)
            positiveArray.push_back(val);
    }

    while (negativeArray.size() < 15) {
        negativeArray.push_back(0);
    }
    while (positiveArray.size() < 15) {
        positiveArray.push_back(0);
    }

    printArray(negativeArray, isHuman);
    printArray(positiveArray, isHuman);

    return 0;
}
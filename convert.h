#include <iostream>
#include <cstring>
#include <fstream>

inline void insymbol(const char *result, char arrayforsymbol[]);

int romanToInt(char symbol) {
    switch (symbol) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            throw "wrong integer";
    }
}

inline long long innumber(const char *result) {
    long long number = 0;
    int prevValue = 0;

    for (int i = static_cast<int>(strlen(result) - 1); i >= 0; i--) {
        int currValue = romanToInt(result[i]);

        if (currValue < prevValue) {
            number -= currValue;
        } else {
            number += currValue;
        }

        prevValue = currValue;
    }
    if (number > 3999) {
        throw "wrong integer";
    }
    char array[128]{};
    char array1[5]{};
    long long number1 = number;
    array1[0] = static_cast<char>(number1 / 1000 % 10 + '0');
    array1[1] = static_cast<char>(number1 / 100 % 10 + '0');
    array1[2] = static_cast<char>(number1 / 10 % 10 + '0');
    array1[3] = static_cast<char>(number1 % 10 + '0');
    array1[4] = '\0';
    insymbol(array1, array);
    for (int i = 0; array[i] != '\0' || result[i] != '\0'; ++i) {
        if (array[i] != result[i]) {
            throw "wrong integer";
        }
    }
    return number;
}

inline void insymbol(const char *result, char arrayforsymbol[]) {
    const char *Romannumbers1[]{"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    const int Romannumbers2[]{1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    int number = 0;
    for (int i = 0; result[i] != '\0'; ++i) {
        number = number * 10 + (result[i] - '0');
    }
    if (number > 3999) {
        throw "wrong integer";
    }
    int i = sizeof(Romannumbers2) / sizeof(Romannumbers2[0]) - 1;
    int index = 0;
    for (; number > 0 && i >= 0; --i) {
        while (number >= Romannumbers2[i]) {
            for (int j = 0; Romannumbers1[i][j] != '\0'; ++j) {
                arrayforsymbol[index++] = Romannumbers1[i][j];
            }
            number -= Romannumbers2[i];
        }
    }
}

void check(const char *result,std::ostream &out) {
    int quantity = 0;
    int quantity1 = 0;
    int i = 0;
    for (; result[i] != '\0'; ++i) {
        if ((result[i] >= 'a' && result[i] <= 'z') || (result[i] >= 'A' && result[i] <= 'Z')) {
            ++quantity;
        } else if (result[i] - '0' >= 0 && result[i] - '0' <= 9) {
            ++quantity1;
        }
    }
    if ((quantity1 != i) && (quantity != i)) {
        throw "wrong integer";
    }
    if (quantity1 == i) {
        char array[128]{};
        insymbol(result, array);
        for (int j = 0; array[j] != '\0'; ++j) {
            out << array[j];
        }
    } else if (quantity == i) {
        out << innumber(result);
    }
}

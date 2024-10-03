#include <iostream>
#include <cstring>
#include <fstream>

inline void convertToRoman(const char *numberStr, char romanResult[]);

int romanCharToInt(char symbol) {
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

inline long long romanToInt(const char *romanStr) {
    long long number = 0;
    int prevValue = 0;

    for (int i = static_cast<int>(strlen(romanStr) - 1); i >= 0; i--) {
        int currValue = romanCharToInt(romanStr[i]);

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

    char romanConverted[128]{};
    char digitsStr[5]{};
    long long tempNumber = number;

    digitsStr[0] = static_cast<char>(tempNumber / 1000 % 10 + '0');
    digitsStr[1] = static_cast<char>(tempNumber / 100 % 10 + '0');
    digitsStr[2] = static_cast<char>(tempNumber / 10 % 10 + '0');
    digitsStr[3] = static_cast<char>(tempNumber % 10 + '0');
    digitsStr[4] = '\0';

    convertToRoman(digitsStr, romanConverted);

    for (int i = 0; romanConverted[i] != '\0' || romanStr[i] != '\0'; ++i) {
        if (romanConverted[i] != romanStr[i]) {
            throw "wrong integer";
        }
    }

    return number;
}

inline void convertToRoman(const char *numberStr, char romanResult[]) {
    const char *romanSymbols[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    const int romanValues[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};

    int number = 0;
    for (int i = 0; numberStr[i] != '\0'; ++i) {
        number = number * 10 + (numberStr[i] - '0');
    }

    if (number > 3999) {
        throw "wrong integer";
    }

    int i = sizeof(romanValues) / sizeof(romanValues[0]) - 1;
    int index = 0;

    while (number > 0 && i >= 0) {
        while (number >= romanValues[i]) {
            for (int j = 0; romanSymbols[i][j] != '\0'; ++j) {
                romanResult[index++] = romanSymbols[i][j];
            }
            number -= romanValues[i];
        }
        --i;
    }

    romanResult[index] = '\0';
}

void checkInput(const char *inputStr, std::ostream &out) {
    int letterCount = 0;
    int digitCount = 0;
    int i = 0;

    for (; inputStr[i] != '\0'; ++i) {
        if ((inputStr[i] >= 'a' && inputStr[i] <= 'z') || (inputStr[i] >= 'A' && inputStr[i] <= 'Z')) {
            ++letterCount;
        } else if (inputStr[i] >= '0' && inputStr[i] <= '9') {
            ++digitCount;
        }
    }

    if ((digitCount != i) && (letterCount != i)) {
        throw "wrong integer";
    }

    if (digitCount == i) {
        char romanResult[128]{};
        convertToRoman(inputStr, romanResult);
        out << romanResult;
    } else if (letterCount == i) {
        out << romanToInt(inputStr);
    }
}

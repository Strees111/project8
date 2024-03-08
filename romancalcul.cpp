#include <iostream>
#include <fstream>
#include "convert.h"

int arithmeticsNumbers(int numbers[], char ch, int i) {
    switch (ch) {
        case ('-'):
            return numbers[i - 1] - numbers[i];
        case ('+'):
            return numbers[i - 1] + numbers[i];
        case ('*'):
            return numbers[i - 1] * numbers[i];
        case ('/'):
            return numbers[i - 1] / numbers[i];
        default:
            return 0;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Use " << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }
    std::ifstream infin(argv[1]);
    if (!infin.is_open()) {
        std::cout << "Can not open to file " << argv[1] << std::endl;
        infin.close();
        return 2;
    }
    std::ofstream outfin(argv[2]);
    if (!outfin.is_open()) {
        std::cout << "Can not open to file " << argv[2] << std::endl;
        outfin.close();
        return 3;
    }
    int stack[128] = {};
    char stack1[128] = {};
    char roman[128] = {};
    int c;
    int i = 0;
    int k = -1;
    while ((c = infin.get()) != EOF) {
        if (c != '\n') {
            outfin << static_cast<char>(c);
        }
        if ((c == '/' || c == '*' || c == '+' || c == '-') && k >= 1) {
            stack[k - 1] = arithmeticsNumbers(stack, static_cast<char>(c), k);
            stack[k--] = 0;
        } else {
            if (c == ' ' && i != 0) {
                roman[i] = '\0';
                stack[++k] = static_cast<int>(innumber(roman));
                i = 0;
            } else if (c != ' ' && c != '\n') {
                roman[i++] = static_cast<char>(c);
            }
        }
        if (c == '\n') {
            if (stack[k] > 0 && stack[k] < 4000) {
                for (int j = 0; j < 128; ++j) {
                    stack1[j] = '\0';
                }
                int count = 1;
                for (int j = 0; j < 128; ++j) {
                    stack1[j] = static_cast<char>(stack[k] % 10 + '0');
                    stack[k] /= 10;
                    if (stack[k] != 0) {
                        ++count;
                    }
                }
                for (int j = 0, q = count - 1; q >= j; ++j, --q) {
                    std::swap(stack1[j], stack1[q]);
                }
                for (int j = 0; j < 128; ++j) {
                    stack[j] = '\0';
                }
                for (int j = count; j < 128; ++j) {
                    stack1[j] = '\0';
                }
                outfin << " = ";
                check(stack1, outfin);
                k = 0;
                outfin << '\n';
            } else {
                outfin << " = ERR";
                --k;
                outfin << '\n';
            }
        }
    }
    if (stack[k] > 0){
        if (stack[k] > 0 && stack[k] < 4000) {
            for (int j = 0; j < 128; ++j) {
                stack1[j] = '\0';
            }
            int count = 1;
            for (int j = 0; j < 128; ++j) {
                stack1[j] = static_cast<char>(stack[k] % 10 + '0');
                stack[k] /= 10;
                if (stack[k] != 0) {
                    ++count;
                }
            }
            for (int j = 0, q = count - 1; q >= j; ++j, --q) {
                std::swap(stack1[j], stack1[q]);
            }
            for (int j = 0; j < 128; ++j) {
                stack[j] = '\0';
            }
            for (int j = count; j < 128; ++j) {
                stack1[j] = '\0';
            }
            outfin << " = ";
            check(stack1, outfin);
        }
        else {
            outfin << " = ERR";
            --k;
            outfin << '\n';
        }
    }
    outfin.close();
    infin.close();
    return 0;
}
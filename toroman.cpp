#include <iostream>
#include <fstream>
#include "convert.h"

int main(int argc, char *argv[]) {
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
    char c{};
    int i = 0;
    char prev{'\n'};
    bool p = true;
    char number[256]{};
    while (infin.get(c)) {
        if (isdigit(c) && (prev == '(' || prev == ' ' || prev == '\n')) {
            number[i++] = c;
            p = false;
        } else if ((c == ')' || c == ' ' || c == '-' || c == '\n') && !p) {
            number[i] = '\0';
            if (atoi(number) > 0 && atoi(number) < 4000) {
                check(number, outfin);
            }
            prev = c;
            outfin << c;
            p = true;
            i = 0;
        } else {
            number[i] = '\0';
            outfin << number;
            prev = c;
            outfin.put(c);
            p = true;
            i = 0;
        }
    }
    if (!p) {
        number[i] = '\0';
        check(number, outfin);
    }
    infin.close();
    outfin.close();
    return 0;
}
#include "include/five.hpp"
#include <cstdio>
#include <iostream>

int main() {
    unsigned char * num;
    int size = 6;
    Five f1 = Five("21");
    Five f2 = Five(f1);

    std::cout << &f1 << " " << &f2 << std::endl;
    return 0;
}
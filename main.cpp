#include "include/five.hpp"
#include <cstdio>

int main() {
    unsigned char * num;
    int size = 6;
    Five f = Five("21");
    Five f2 = Five("3");
    printf("%s %s \n", f.getString().c_str(), f2.getString().c_str());
    Five fres = f - f2;
    printf("%s\n", fres.getString().c_str());
    return 0;
}
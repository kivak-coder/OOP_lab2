#include "../include/five.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <stdexcept>

void Five::validateDigit(unsigned char digit) {
    if (digit > '4' || digit < '0') {
        throw std::invalid_argument("Invalid digit for base-5 number: " + std::to_string(digit));
    }
}

void Five::removeLeadingZeros() {
    if (size == 0) return;
    
    size_t newSize = size;
    for (size_t i = size; i > 0; --i) {
        if (digits[i - 1] != 0) break;
        newSize = i - 1;
    }
    
    if (newSize == 0) {
        delete[] digits;
        digits = new unsigned char[1];
        digits[0] = 0;
        size = 1;

    } else if (newSize != size) {
        unsigned char* newDigits = new unsigned char[newSize];
        for (size_t i = 0; i < newSize; ++i) {
            newDigits[i] = digits[i];
        }
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

int Five::compare(const Five& other) {
    if (this->size > other.size) {return 1;}
    if (this->size < other.size) {return -1;}

    for (int i = 0; i < this->size; ++i) {
        if (this->digits[i] > other.digits[i]) {
            return 1;
        }
        if (this->digits[i] < other.digits[i]) {
            return -1;
        }
        if (this->digits[i] == other.digits[i]) {
            continue;;
        }
    }
    return 0;
}

Five::Five() {
    digits = new unsigned char (1);
    size = 1;
    digits[0] = 0;
}


Five::Five(const std::string& string) {
    if (string.empty()) {
        Five(); // check if constructor calling is right
    }
    
    size = string.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        unsigned char c = string[size - 1 - i];
        validateDigit(c);
        digits[i] = c;
    }
    
    removeLeadingZeros();
}

Five::Five(const Five& other) {
    size = other.size;
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

Five::Five(const size_t& n, unsigned char c) {
    if (n == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    validateDigit(c);
    size = n;
    digits = new unsigned char[n];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = c;
    }
}

Five::~Five() {
    delete[] digits;
    size = 0;
}

Five Five::operator+(const Five& other) {
    bool add = false;
    int sum = 0;

    Five newNum = Five();
    newNum.size = std::max(this->size, other.size);
    newNum.digits = new unsigned char (newNum.size);
    
    for (int i = 0; i < std::min(this->size, other.size); i++) {
        sum = (this->digits[i] - '0') + (other.digits[i] - '0');
        if (add) {
            sum++;
            add = false;
        }
        if (sum >= 5) {
            add = true;
            newNum.digits[i] = sum - 5 + '0';
        } else {
            newNum.digits[i] = sum + '0';
        }
    }
    for (int j = std::min(this->size, other.size); j < newNum.size; ++j) {
        if (sum >= 5) {
            add = true;
        }
        if (this->size > other.size) {
            sum = this->digits[j] - '0';
        } else {
            sum = other.digits[j] - '0';    
        }
        if (add) {
            sum++;
            add = false;
        }
        newNum.digits[j] = sum + '0';

    }
    if (add) {
        unsigned char * tmp = new unsigned char (newNum.size + 1);
        tmp[newNum.size] = '1'; 
        newNum.digits = tmp;
        ++newNum.size;
        delete tmp;
    }
    return newNum;
}

Five Five::operator-(const Five& other) { 
    if (compare(other) == -1) {
        throw std::invalid_argument("Result would be negative");
    }
    
    if (compare(other) == 0) {
        return Five(); 
    }
    
    size_t maxSize = this->size;
    unsigned char* result = new unsigned char[maxSize]();
    
    unsigned char borrow = 0;
    int diff = 0;
    int digit_this = 0;
    int digit_other = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        if (i < this->size) {
            digit_this = this->digits[i] - '0';
        } else {
            digit_this = 0;
        }
        if (i < other.size) {
            digit_other = other.digits[i] - '0';
        } else {
            digit_other = 0;
        }

        diff = digit_this - digit_other - borrow;
        if (diff < 0) {
            diff += 5;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[i] = diff + '0';
    }
    
    Five five;
    five.digits = result;
    five.size = maxSize;
    five.removeLeadingZeros();
    
    return five;
}

bool Five::operator>(const Five& other) {
    return compare(other) > 0;
}

bool Five::operator<(const Five& other) {
    return compare(other) < 0;
}

bool Five::operator==(const Five& other) {
    return compare(other) == 0;
}

Five Five::operator=(const Five& other) {
    if (*this == (Five)other) {
        return *this;
    }
    unsigned char * newArray = new unsigned char (other.size);
    for (int i = 0; i < other.size; ++i) {
        newArray[i] = other.digits[i];
    }
    this->size = other.size;
    this->digits = newArray;
    return *this;
}

std::string Five::getString() {
    removeLeadingZeros();
    std::string resString;
    if (size == 0) {
        resString = "0";
    }
    for (int i = 0; i < size; i++) {
        resString.push_back(digits[size - i - 1]);
    }
    return resString;

}

size_t Five::getSize() {
    return size;
}

unsigned char Five::getDigit(size_t index) {
    return this->digits[index];
    
}


# include "task.h"

Octal::Octal() : digits(nullptr), o_size(0) {}
Octal::Octal(const size_t n, unsigned char t) {
    if (n == 0) {
        throw invalid_argument("Size cannot be zero");
    }
    if (t > 7) {
        throw invalid_argument("Octal digit must be 0-7");
    }
    o_size = n;
    digits = new unsigned char[o_size];
    for (size_t i = 0; i < o_size; ++i) {
        digits[i] = t;
    }
    normal();
}

Octal::Octal(const initializer_list<unsigned char>& list) {
    if (list.size()==0) {
        throw invalid_argument("Initializer list is empty");
    }
    o_size = list.size();
    digits = new unsigned char[o_size];
    size_t i = 0;
    for (unsigned char d : list) {
        if (d > 7) {
            delete[] digits;
            throw invalid_argument("Digit in initializer_list must be 0-7");
        }
        digits[o_size - i - 1] = d; //разворачиваем
        ++i;
    }
    normal();
}

Octal::Octal(const string& octStr) {
    if (octStr.empty()) {
        throw invalid_argument("Empty string");
    }
    o_size = octStr.size();
    digits = new unsigned char[o_size];

    for (size_t i = 0; i < o_size; ++i) {
        char c = octStr[o_size - 1 - i]; 
        if (c < '0' || c > '7') {
            delete[] digits;
            throw invalid_argument("Invalid octal character");
        }
        digits[i] = c - '0';
    }
    normal();
}

Octal::Octal(const Octal& other) : o_size(other.o_size) {
    digits = new unsigned char[o_size];
    for (size_t i = 0; i < o_size; ++i) {
        digits[i] = other.digits[i];
    }
}

Octal::~Octal() noexcept {
    delete[] digits;
}

void Octal::normal() {
    size_t new_size = o_size;
    while (new_size > 1 && digits[new_size - 1] == 0) {
        --new_size;
    }

    if (new_size != o_size) {
        unsigned char* new_digits = new unsigned char[new_size];
        for (size_t i = 0; i < new_size; ++i) {
            new_digits[i] = digits[i];
        }
        delete[] digits;
        digits = new_digits;
        o_size = new_size;
    }
}

Octal Octal::add(const Octal& other) const {
    size_t max_size = (o_size > other.o_size) ? o_size : other.o_size;
    Octal result;
    delete[] result.digits;
    result.digits = new unsigned char[max_size + 1];
    result.o_size = max_size + 1;

    unsigned char carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        unsigned short sum = carry;
        if (i < o_size) sum += digits[i];
        if (i < other.o_size) sum += other.digits[i];
        result.digits[i] = sum % 8;
        carry = sum / 8;
    }
    result.digits[max_size] = carry;

    result.normal();
    return result;
}

Octal Octal::subtract(const Octal& other) const {
    if (less(other)) {
        throw underflow_error("It'ы negative");
    }
    unsigned char* temp = new unsigned char[o_size];
    unsigned char borrow = 0;

    for (size_t i = 0; i < o_size; ++i) {
        unsigned char d1 = digits[i];
        unsigned char d2 = (i < other.o_size) ? other.digits[i] : 0;

        if (d1 < d2 + borrow) {
            temp[i] = d1 + 8 - d2 - borrow;
            borrow = 1;
        } else {
            temp[i] = d1 - d2 - borrow;
            borrow = 0;
        }
    }

    Octal result;
    delete[] result.digits;
    result.digits = temp;
    result.o_size = o_size;
    result.normal();
    return result;
}

bool Octal::equals(const Octal& other) const {
    if (o_size != other.o_size) return false;
    for (size_t i = 0; i < o_size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Octal::less(const Octal& other) const {
    if (o_size != other.o_size) {
        return o_size < other.o_size;
    }
    for (size_t i = o_size; i > 0; --i) {
        size_t idx = i - 1;
        if (digits[idx] < other.digits[idx]) return true;
        if (digits[idx] > other.digits[idx]) return false;
    }
    return false;}

bool Octal::greater(const Octal& other) const {
    if (o_size != other.o_size) {
        return o_size > other.o_size;
    }
    for (size_t i = o_size; i > 0; --i) {
        size_t idx = i - 1;
        if (digits[idx] > other.digits[idx]) return true;
        if (digits[idx] < other.digits[idx]) return false;
    }
    return false; 
}

unsigned int Octal::toDecimal() const {
    unsigned int dec = 0;
    unsigned int power = 1;
    for (size_t i = 0; i < o_size; ++i) {
        dec += digits[i] * power;
        if (i < o_size - 1){
            power *= 8; 
        }
    }
    return dec;
}

string Octal::toString() const {
    if (o_size == 0) return "0";
    string s;
    s.reserve(o_size);
    for (size_t i = 0; i < o_size; ++i) {
        s.push_back('0' + digits[o_size - 1 - i]);
    }
    return s;
}
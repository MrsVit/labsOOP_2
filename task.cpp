#include "task.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

Octal::Octal() : digits(1, 0) {}
Octal::Octal(const size_t n, unsigned char t) {
    if (t > 7) {
        throw invalid_argument("All digits must be in range 0-7");
    }
    digits.resize(n, t);
    normal();
}
Octal::Octal(const initializer_list<unsigned char>& list) {
    for (auto digit : list) {
        if (digit >7) {
        throw invalid_argument("All digits must be in range 0-7");
        }
    }
    digits.assign(list.begin(), list.end());
    normal();
}
Octal::Octal(const string&  s) {
    if ( s.empty()) {
        digits = {0};
        return;
    }
    for (char c :  s) {
        if (!isdigit(c) || c > '7') {
        throw invalid_argument("All digits must be in range 0-7");
        }
    }
    digits.reserve( s.size());
    for (char c :  s) {
        digits.push_back(static_cast<unsigned char>(c - '0'));
    }
    normal();
}

Octal::Octal(const Octal& other) : digits(other.digits) {}
Octal::~Octal() noexcept = default;

void Octal::normal() {
    auto  i= digits.begin();
    while ( i!= digits.end() && * i== 0 && distance(i, digits.end()) > 1) {
        ++i;
    }
    digits.erase(digits.begin(), i);
    if (digits.empty()) {
        digits = {0};
    }
}
unsigned int Octal::toDecimal() const {
    unsigned int res = 0;
    unsigned int base = 1;
    for (auto i = digits.rbegin(); i != digits.rend(); ++i) {
        res += (*i) * base;
        base *= 8;
    }
    return res;
}

string Octal::toString() const {
    string result;
    for (unsigned char digit : digits) {
        result += static_cast<char>('0' + digit);
    }
    return result;
}

//cложение b вычитание? что вeрнут новое число-объект
Octal Octal::add(const Octal& other) const {
    Octal result;
    result.digits.clear();
    auto  a = digits.rbegin();
    auto  b = other.digits.rbegin();
    unsigned char  c = 0;

    while ( a != digits.rend() ||  b != other.digits.rend() ||  c) {
        unsigned char sum =  c;
        if ( a != digits.rend()) {
            sum += * a++;
        }
        if ( b != other.digits.rend()) {
            sum += * b++;
        }
         c = sum / 8;
        result.digits.push_back(sum % 8);
    }
    reverse(result.digits.begin(), result.digits.end());
    result.normal();
    return result;
}

Octal Octal::subtract(const Octal& other) const {
    if (this->less(other)) {
        throw std::invalid_argument("Cannot subtract larger number from smaller (unsigned)");
    }

    Octal result;
    result.digits.clear();

    auto  a = digits.rbegin();
    auto  b = other.digits.rbegin();
    int  k = 0;

    while ( a != digits.rend()) {
        int  d = * a++ -  k;
        if ( b != other.digits.rend()) {
             d -= * b++;
        }
        if ( d < 0) {
             d += 8;
             k = 1;
        } else {
             k = 0;
        }
        result.digits.push_back(static_cast<unsigned char>( d));
    }
    reverse(result.digits.begin(), result.digits.end());
    result.normal();
    return result;
}

bool Octal::equals(const Octal& other) const {
    if (digits.size() != other.digits.size()) {
        return false;
    }
    return equal(digits.begin(), digits.end(), other.digits.begin());
}

bool Octal::less(const Octal& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    return lexicographical_compare(digits.begin(), digits.end(),
                                        other.digits.begin(), other.digits.end());
}

bool Octal::greater(const Octal& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }
    return lexicographical_compare(other.digits.begin(), other.digits.end(),
                                        digits.begin(), digits.end());
}

//сложенни и вычитание, которые изменят текущий объект
Octal& Octal::Add(const Octal& other) {
    *this = this->add(other);
    return *this;
}

Octal& Octal::Sub(const Octal& other) {
    *this = this->subtract(other);
    return *this;
}
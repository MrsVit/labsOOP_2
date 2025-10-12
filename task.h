#pragma once
# include <string>
# include <iostream>
# include <algorithm>

using namespace std; 

class Octal{
    public:
        Octal();
        Octal(const size_t n, unsigned char t = 0); 
        Octal(const initializer_list<unsigned char>& list);
        Octal(const string& octStr); 
        Octal(const Octal& other);     
        virtual ~Octal() noexcept;    

        //геттеры
        unsigned int toDecimal() const;
        string toString() const;
        size_t size() const { return o_size; }

        Octal add(const Octal& other) const;
        Octal subtract(const Octal& other) const;
        bool equals(const Octal& other) const;
        bool less(const Octal& other) const;
        bool greater(const Octal& other) const;

    private:
        unsigned char * digits;
        size_t o_size;
        void normal(); 
};
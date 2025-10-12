#include "task.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isValidOctal(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < '0' || c > '7') return false;
    }
    return true;
}

int main() {
    cout<<"=====Demo methods of initialization===="<<endl;
    Octal zero;
    cout << "1. Default constructor: " << zero.toString() << endl;
    Octal repeated(4, 5);
    cout << "2. Repeated digit (4, '5'): " << repeated.toString() << endl;
    Octal from_list({7, 2, 1}); 
    cout << "3. From initializer_list {7,2,1}: " << from_list.toString() << endl;
    Octal from_str("642");
    cout << "4. From string \"642\": " << from_str.toString() << endl;

    cout << "\n=== Main part ===" << endl;
    string a;
    cout << "Enter first octal number A (digits 0-7): ";
    cin >> a;

    if (!isValidOctal(a)) {
        cerr << "Only 0-7" << endl;
        return 1;
    }

    Octal A(a);
    cout << "A = " << A.toString() << " (decimal: " << A.toDecimal() << ")" << endl;

    char choice;
    cout << "\nHow to set B?\n"
         << "  1. Enter manually\n"
         << "  2. Copy from A\n"
         << "Choose (1 or 2): ";
    cin >> choice;

    Octal B;
    if (choice == '2') {
        B = A; 
        cout << "B was set by copying A." << endl;
    } else if (choice == '1') {
        string inputB;
        cout << "Enter second octal number B: ";
        cin >> inputB;
        if (!isValidOctal(inputB)) {
            cerr << "Only 0-7" << endl;
            return 1;
        }
        B = Octal(inputB);
        cout << "B = " << B.toString() << " (decimal: " << B.toDecimal() << ")" << endl;
    } else {
        cerr << "Invalid choice. Exiting." << endl;
        return 1;
    }

    try {
        Octal sum = A.add(B);
        cout << "A + B = " << sum.toString() << " (dec: " << sum.toDecimal() << ")" << endl;
    } catch (const exception& e) {
        cerr << "Addition error: " << e.what() << endl;
    }

    try {
        Octal diff = A.subtract(B);
        cout << "A - B = " << diff.toString() << " (dec: " << diff.toDecimal() << ")" << endl;
    } catch (const exception& e) {
        cout << "A - B: " << e.what() << " (cannot be negative)" << endl;
    }

    cout << "A ?= B? " << (A.equals(B) ? "yes" : "no") << endl;
    cout << "A ?< B?  " << (A.less(B) ? "yes" : "no") << endl;
    cout << "A ?> B?  " << (A.greater(B) ? "yes" : "no") << endl;

    cout << "\nProgram completed." << endl;
    return 0;
}
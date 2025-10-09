#include "task.h"
#include <iostream>
#include <string>
#include <exception>
using namespace std;

int main() {
    cout << "=== Octal Number Calculator ===" << endl;
    cout << "Supported commands:" << endl;
    cout << "  create <name> <octal_str>   -- create a number (digits 0-7 only)" << endl;
    cout << "  print <name>               -- print in octal and decimal" << endl;
    cout << "  add <A> <B>                -- compute A + B" << endl;
    cout << "  sub <A> <B>                -- compute A - B" << endl;
    cout << "  cmp <A> <B>                -- compare A and B" << endl;
    cout << "  quit                       -- exit the program" << endl;
    cout << "----------------------------------------" << endl;

    Octal A, B;
    bool hasA = false, hasB = false;
    string cmd;

    while (cin >> cmd) {
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "create") {
            string name, value;
            cin >> name >> value;
            try {
                if (name == "A") {
                    A = Octal(value);
                    hasA = true;
                    cout << "Number A = " << A.toString() << " created." << endl;
                } else if (name == "B") {
                    B = Octal(value);
                    hasB = true;
                    cout << "Number B = " << B.toString() << " created." << endl;
                } else {
                    cout << "Please use name 'A' or 'B'." << endl;
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (cmd == "print") {
            string name;
            cin >> name;
            if (name == "A" && hasA) {
                cout << "A = " << A.toString() << " (octal) = " << A.toDecimal() << " (decimal)" << endl;
            } else if (name == "B" && hasB) {
                cout << "B = " << B.toString() << " (octal) = " << B.toDecimal() << " (decimal)" << endl;
            } else {
                cout << "Number " << name << " hasn't created." << endl;
            }
        }
        else if (cmd == "add") {
            if (!hasA || !hasB) {
                cout << "Please create both" << endl;
                continue;
            }
            Octal result = A.add(B);
            cout << A.toString() << " + " << B.toString() << " = " << result.toString()
                 << " (decimal: " << result.toDecimal() << ")" << endl;
        }
        else if (cmd == "sub") {
            if (!hasA || !hasB) {
                cout << "Please create both" << endl;
                continue;
            }
            try {
                Octal result = A.subtract(B);
                cout << A.toString() << " - " << B.toString() << " = " << result.toString()
                     << " (decimal: " << result.toDecimal() << ")" << endl;
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (cmd == "cmp") {
            if (!hasA || !hasB) {
                cout << "Please create both" << endl;
                continue;
            }
            if (A.equals(B)) {
                cout << A.toString() << " == " << B.toString() << endl;
            } else if (A.less(B)) {
                cout << A.toString() << " < " << B.toString() << endl;
            } else if (A.greater(B)) {
                cout << A.toString() << " > " << B.toString() << endl;
            }
        }
        else {
            cout << "Unknown cmand" << endl;
        }
    }
    return 0;
}
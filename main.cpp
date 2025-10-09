#include "task.h"
#include <iostream>
#include <string>
#include <exception>
using namespace std;

int main() {
    cout << "=== Octal Calculator ===" << endl;
    cout << "Available commands:" << endl;
    cout << "  create <name> <octal>   -- make a new octal number (only 0-7)" << endl;
    cout << "  print <name>            -- show number in octal & decimal" << endl;
    cout << "  add <A> <B>             -- add two numbers" << endl;
    cout << "  sub <A> <B>             -- subtract B from A" << endl;
    cout << "  cmp <A> <B>             -- compare A and B" << endl;
    cout << "  quit                    -- exit" << endl;
    cout << "----------------------------------------" << endl;

    Octal A, B;
    bool A_ready = false, B_ready = false;
    string command;

    while (cin >> command) {
        if (command == "quit") {
            break;
        }
        else if (command == "create") {
            string var_name, oct_str;
            cin >> var_name >> oct_str;
            try {
                if (var_name == "A") {
                    A = Octal(oct_str);
                    A_ready = true;
                    cout << "Created A = " << A.toString() << endl;
                }
                else if (var_name == "B") {
                    B = Octal(oct_str);
                    B_ready = true;
                    cout << "Created B = " << B.toString() << endl;
                }
                else {
                    cout << "Use 'A' or 'B' as name, please." << endl;
                }
            }
            catch (const exception& ex) {
                cout << "Oops: " << ex.what() << endl;
            }
        }
        else if (command == "print") {
            string name;
            cin >> name;
            if (name == "A" && A_ready) {
                cout << "A is " << A.toString() << " (oct) = " << A.toDecimal() << " (dec)" << endl;
            }
            else if (name == "B" && B_ready) {
                cout << "B is " << B.toString() << " (oct) = " << B.toDecimal() << " (dec)" << endl;
            }
            else {
                cout << "Number " << name << " not found. Create it first." << endl;
            }
        }
        else if (command == "add") {
            if (!A_ready || !B_ready) {
                cout << "Both A and B must exist." << endl;
                continue;
            }
            Octal sum = A.add(B);
            cout << A.toString() << " + " << B.toString() << " = " << sum.toString()
                 << " (dec: " << sum.toDecimal() << ")" << endl;
        }
        else if (command == "sub") {
            if (!A_ready || !B_ready) {
                cout << "Need both numbers to subtract." << endl;
                continue;
            }
            try {
                Octal diff = A.subtract(B);
                cout << A.toString() << " - " << B.toString() << " = " << diff.toString()
                     << " (dec: " << diff.toDecimal() << ")" << endl;
            }
            catch (const exception& ex) {
                cout << "Error during subtraction: " << ex.what() << endl;
            }
        }
        else if (command == "cmp") {
            if (!A_ready || !B_ready) {
                cout << "Can't compare — missing numbers." << endl;
                continue;
            }
            if (A.equals(B)) {
                cout << A.toString() << " equals " << B.toString() << endl;
            }
            else if (A.less(B)) {
                cout << A.toString() << " is less than " << B.toString() << endl;
            }
            else {
                cout << A.toString() << " is greater than " << B.toString() << endl;
            }
        }
        else {
            cout << "Don't know that command." << endl;
        }
    }

    return 0;
}
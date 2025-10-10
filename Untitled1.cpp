#include <bits/stdc++.h>  // Always at the top
using namespace std;

int main() {
    cout << "WELCOME TO STACK IMPLEMENTATION" << endl;
    stack<string> stk;
    bool run = true;
    char number;

    while (run) {
        cout << "\n1 => Push\n";
        cout << "2 => Pop\n";
        cout << "3 => Size\n";
        cout << "4 => Empty\n";
        cout << "5 => Peek\n";
        cout << "PRESS Q TO QUIT\n";

        cout << "\nENTER THE OPTION: ";
        cin >> number;

        switch (number) {
            case '1': {
                cout << "YOU SELECTED PUSH" << endl;
                string arg1;
                cout << "Enter the item name: ";
                cin.ignore(); // optional, if needed
                getline(cin, arg1);
                stk.push(arg1);
                break;
            }
            case '2': {
                cout << "YOU SELECTED POP" << endl;
                if (!stk.empty()) {
                    cout << "Popped item: " << stk.top() << endl;
                    stk.pop();
                } else {
                    cout << "Stack is empty!" << endl;
                }
                break;
            }
            case '3': {
                cout << "YOU SELECTED SIZE" << endl;
                cout << "Stack size: " << stk.size() << endl;
                break;
            }
            case '4': {
                cout << "YOU SELECTED EMPTY" << endl;
                cout << (stk.empty() ? "Stack is empty" : "Stack is not empty") << endl;
                break;
            }
            case '5': {
                cout << "YOU SELECTED PEEK" << endl;
                if (!stk.empty()) {
                    cout << "Top item: " << stk.top() << endl;
                } else {
                    cout << "Stack is empty!" << endl;
                }
                break;
            }
            case 'Q':
            case 'q': {
                cout << "Exiting program..." << endl;
                run = false;
                break;
            }
            default: {
                cout << "Invalid input! Please select a valid option." << endl;
            }
        }
    }

    return 0;
}

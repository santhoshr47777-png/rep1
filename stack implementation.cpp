#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
#else
    #include <unistd.h>
    #define CLEAR "clear"
#endif

using namespace std;

void typeWriter(string text, int delay = 15) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

void pauseAndClear() {
    cout << "\n🔁 Press Enter to continue...";
    cin.ignore();
    cin.get();
    system(CLEAR);
}

void displayHeader() {
    setColor(11);
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║      🌟 ADVANCED STACK INTERACTIVE TOOL      ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;
    setColor(7);
}

void displayStack(stack<string> stk) {
    cout << "\n📦 STACK CONTENT (Top -> Bottom):" << endl;
    cout << "╔════════════════════════════════╗" << endl;

    if (stk.empty()) {
        cout << "║          (empty stack)         ║" << endl;
    } else {
        while (!stk.empty()) {
            cout << "║ " << setw(31) << left << stk.top() << "║" << endl;
            stk.pop();
        }
    }

    cout << "╚════════════════════════════════╝" << endl;
}

void showMenu() {
    setColor(14);
    cout << "\n🧭 MAIN MENU:" << endl;
    setColor(7);
    cout << " [1] ➕ Push multiple items" << endl;
    cout << " [2] ➖ Pop item" << endl;
    cout << " [3] 📐 Show stack size" << endl;
    cout << " [4] ❓ Check if empty" << endl;
    cout << " [5] 👀 Peek top item" << endl;
    cout << " [6] 🔁 Reverse stack" << endl;
    cout << " [Q] ❌ Quit" << endl;
    cout << "\nEnter your choice: ";
}

void pushItems(stack<string> &stk) {
    cin.ignore();
    cout << "📝 Enter items (separated by commas): ";
    string input;
    getline(cin, input);

    size_t pos = 0;
    while ((pos = input.find(',')) != string::npos) {
        string token = input.substr(0, pos);
        stk.push(token);
        input.erase(0, pos + 1);
    }
    if (!input.empty()) {
        stk.push(input);
    }

    setColor(10);
    cout << "✅ Items pushed successfully." << endl;
    setColor(7);
}

void popItem(stack<string> &stk) {
    if (stk.empty()) {
        setColor(12);
        cout << "❌ Stack is empty. Nothing to pop!" << endl;
    } else {
        setColor(10);
        cout << "🗑️  Popped: " << stk.top() << endl;
        stk.pop();
    }
    setColor(7);
}

void showSize(stack<string> &stk) {
    setColor(11);
    cout << "📐 Current stack size: " << stk.size() << endl;
    setColor(7);
}

void checkEmpty(stack<string> &stk) {
    if (stk.empty()) {
        setColor(10);
        cout << "✅ Stack is empty." << endl;
    } else {
        setColor(14);
        cout << "⚠️  Stack is not empty. Size: " << stk.size() << endl;
    }
    setColor(7);
}

void peekItem(stack<string> &stk) {
    if (stk.empty()) {
        setColor(12);
        cout << "❌ Stack is empty." << endl;
    } else {
        setColor(11);
        cout << "👁️  Top of the stack: " << stk.top() << endl;
    }
    setColor(7);
}

void reverseStack(stack<string> &stk) {
    if (stk.empty()) {
        setColor(12);
        cout << "❌ Stack is empty. Cannot reverse." << endl;
        setColor(7);
        return;
    }

    vector<string> temp;
    while (!stk.empty()) {
        temp.push_back(stk.top());
        stk.pop();
    }

    for (string &item : temp) {
        stk.push(item);
    }

    setColor(10);
    cout << "🔁 Stack reversed successfully." << endl;
    setColor(7);
}

int main() {
    stack<string> stk;
    char choice;
    bool run = true;
    SetConsoleOutputCP(CP_UTF8);

    while (run) {
        system(CLEAR);
        displayHeader();
        displayStack(stk);
        showMenu();
        cin >> choice;

        switch (choice) {
            case '1': pushItems(stk); break;
            case '2': popItem(stk); break;
            case '3': showSize(stk); break;
            case '4': checkEmpty(stk); break;
            case '5': peekItem(stk); break;
            case '6': reverseStack(stk); break;
            case 'Q':
            case 'q':
                typeWriter("\n👋 Thank you for using the Stack Tool. Goodbye!\n", 25);
                run = false;
                break;
            default:
                setColor(12);
                cout << "❗ Invalid option! Try again." << endl;
                setColor(7);
        }

        if (run) pauseAndClear();
    }

    return 0;
}

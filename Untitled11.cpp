#include <windows.h>
#include <stack>
#include <string>
#include <sstream>

std::stack<std::string> stk;
HWND hInput, hStackDisplay;

void RefreshDisplay(HWND hwnd) {
    std::stringstream ss;
    ss << "Top -> Bottom\n----------------\n";

    std::stack<std::string> temp = stk;
    if (temp.empty()) {
        ss << "(empty stack)";
    } else {
        while (!temp.empty()) {
            ss << temp.top() << "\n";
            temp.pop();
        }
    }

    SetWindowText(hStackDisplay, ss.str().c_str());
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            CreateWindow("STATIC", "Enter Item:", WS_VISIBLE | WS_CHILD,
                         20, 20, 80, 25, hwnd, NULL, NULL, NULL);

            hInput = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  110, 20, 150, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "Push", WS_VISIBLE | WS_CHILD,
                         270, 20, 70, 25, hwnd, (HMENU)1, NULL, NULL);

            CreateWindow("BUTTON", "Pop", WS_VISIBLE | WS_CHILD,
                         350, 20, 70, 25, hwnd, (HMENU)2, NULL, NULL);

            hStackDisplay = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_READONLY,
                                         20, 60, 400, 200, hwnd, NULL, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 1: { // Push
                    char text[100];
                    GetWindowText(hInput, text, 100);
                    if (strlen(text) > 0) {
                        stk.push(text);
                        SetWindowText(hInput, "");
                        RefreshDisplay(hwnd);
                    }
                    break;
                }
                case 2: { // Pop
                    if (!stk.empty()) {
                        stk.pop();
                        RefreshDisplay(hwnd);
                    } else {
                        MessageBox(hwnd, "Stack is empty!", "Warning", MB_OK | MB_ICONWARNING);
                    }
                    break;
                }
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hInstance = hInst;
    wc.lpszClassName = "StackAppClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc)) return -1;

    HWND hwnd = CreateWindow("StackAppClass", "Stack GUI - No GDI", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 460, 320, NULL, NULL, NULL, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

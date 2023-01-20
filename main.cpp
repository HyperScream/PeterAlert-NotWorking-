#include <Windows.h>
#include "resources.rc"
#include "resources.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HICON hIcon = NULL;
    switch (msg) {
    case WM_CREATE:
        hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        break;
    case WM_PAINT: {
        if (hIcon != NULL) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            DrawIconEx(hdc, rc.left + (rc.right - rc.left) / 2, rc.top + (rc.bottom - rc.top) / 2, hIcon, 0, 0, 0, NULL, DI_NORMAL);
            EndPaint(hwnd, &ps);
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

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"CustomWindow";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(L"CustomWindow", L"Custom Icon", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(hwnd, SW_SHOW);

    MessageBox(NULL, L"This is a custom icon message box", L"Custom Icon", MB_OK | MB_ICONINFORMATION);

    HICON hIcon = (HICON)GetClassLongPtr(hwnd, GCLP_HICON);
    DestroyIcon(hIcon);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


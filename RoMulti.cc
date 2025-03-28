#include <Windows.h>
#include <iostream>

BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType)
{
    return TRUE;
}

int main()
{
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"HiddenWindowClass";

    if (RegisterClassW(&wc) == 0)
    {
        DWORD error = GetLastError();
        std::cerr << "Failed to register window class: " << error << std::endl;
        return error;
    }

    HWND hWnd = CreateWindowExW(
        WS_EX_TOOLWINDOW,
        wc.lpszClassName,
        L"RoMulti",
        WS_OVERLAPPED,
        0, 0, 0, 0,
        NULL, NULL,
        wc.hInstance,
        NULL);

    if (hWnd == NULL)
    {
        DWORD error = GetLastError();
        std::cerr << "Failed to create window: " << error << std::endl;
        return error;
    }

    FreeConsole();

    HANDLE hMutex = CreateMutexW(NULL, FALSE, L"ROBLOX_singletonMutex");
    if (hMutex == NULL)
    {
        DWORD error = GetLastError();
        std::cerr << "Failed to create mutex: " << error << std::endl;
        DestroyWindow(hWnd);
        return error;
    }

    WaitForSingleObject(hMutex, INFINITE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (hMutex != NULL)
    {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
    }

    DestroyWindow(hWnd);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}
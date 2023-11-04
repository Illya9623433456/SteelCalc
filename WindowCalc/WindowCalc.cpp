// WindowCalc.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowCalc.h"

#define MAX_LOADSTRING 100
#define IDC_SCREEN1 1001
#define IDC_SCREEN2 1002
#define IDC_SCREEN3 1003
#define IDC_BUTTON1 5001
#define IDC_BUTTON2 5002

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Елементи управління
HWND hButton1, hButton2;
HWND hScreen1, hScreen2, hScreen3;
HWND hTotal1, hTotal2, hTotal3;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWCALC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWCALC));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWCALC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWCALC);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            SetWindowText(hWnd, L"Розв`язування квадратних рівнянь");
            MoveWindow(hWnd, 400, 150, 550, 410, true);

            hTotal1 = CreateWindowEx(0, L"STATIC", L"Рівняня:", WS_CHILD | WS_VISIBLE
                | SS_CENTER, 50, 40, 200, 25, hWnd, NULL, hInst, NULL);
            hTotal2 = CreateWindowEx(0, L"STATIC", L"Розв`язок:", WS_CHILD | WS_VISIBLE
                | SS_CENTER, 280, 40, 200, 25, hWnd, NULL, hInst, NULL);
            hTotal3 = CreateWindowEx(0, L"STATIC", L"Всі обчислення:", WS_CHILD | WS_VISIBLE
                | SS_CENTER, 150, 150, 215, 15, hWnd, NULL, hInst, NULL);

            hScreen1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE
                | ES_CENTER, 50, 70, 200, 25, hWnd, NULL, hInst, NULL);
            hScreen2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE
                | ES_CENTER | ES_READONLY, 280, 70, 200, 25, hWnd, NULL, hInst, NULL);
            hScreen3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE
                | ES_CENTER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY, 50, 180, 440, 150,
                hWnd, NULL, hInst, NULL);

            hButton1 = CreateWindowEx(0, L"BUTTON", L"Обчислити вираз", WS_CHILD | WS_VISIBLE,
                50, 100, 200, 30, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
            hButton2 = CreateWindowEx(0, L"BUTTON", L"Очистити все", WS_CHILD | WS_VISIBLE,
                280, 100, 200, 30, hWnd, (HMENU)IDC_BUTTON2, hInst, NULL);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDC_BUTTON1:
            
                TCHAR buff1[64];
                TCHAR buff2[64];
                TCHAR buff3[64];
                GetDlgItemText(hWnd, IDC_SCREEN1, buff1, 64);
                GetDlgItemText(hWnd, IDC_SCREEN2, buff2, 64);
                GetDlgItemText(hWnd, IDC_SCREEN3, buff3, 64);
               
                double a = _wtof(buff1);
                double b = _wtof(buff2);
                double c = _wtof(buff3);

                double d = b * b - 4 * a * c;

                GetWindowText(hScreen1, buff1, 64);
                if (lstrlen(buff1) == 0)
                {
                    MessageBox(hWnd, L" Будь ласка введіть рівнняня!!!",
                        L"Увага", MB_OK | MB_ICONEXCLAMATION);
                    SetFocus(hScreen1);
                    break;
                }
                else if (d > 0)
                {
                    double x1 = (-b + (d)) / (2 * a);
                    double x2 = (-b - (d)) / (2 * a);
                    SetWindowText(hScreen2, buff1);
                }
                else if (d == 0)
                {
                    double x1 = -b / (2 * a);
                    GetWindowText(hScreen3, buff2, 64);
                    lstrcat(buff2, buff1);
                    SetWindowText(hScreen3, buff2);
                }
                else
                {
                    SetWindowText(hScreen2, L"Корені");
                    SetWindowText(hScreen3, L"");
                }
                break;
            case IDC_BUTTON2:
            {
                SetWindowText(hScreen1, L"");
                SetWindowText(hScreen2, L"");
                SetFocus(hScreen1);
            }
            break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
    }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

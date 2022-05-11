#include <windows.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
HWND             create_main_window(HINSTANCE hInst);

HINSTANCE g_hInst = nullptr;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
    auto hWnd = create_main_window(hInst);
    if (hWnd == nullptr)
        return 1;
    g_hInst = hInst;

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_MINGWAPP));

    HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
    InsertMenu(hSysMenu, 5, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
    InsertMenu(hSysMenu, 6, MF_BYPOSITION, ID_HELP_ABOUT, TEXT("About"));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}
HWND create_main_window(HINSTANCE hInst)
{
    WNDCLASSEX wc;
    wc.cbSize        = sizeof(wc);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 0, 0,
                                        LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
    wc.hIconSm       = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    wc.hCursor       = (HCURSOR)LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MAINMENU);
    wc.lpszClassName = TEXT("mingw_window");
    if (RegisterClassEx(&wc) == 0) {
        return nullptr;
    }
    return CreateWindow(wc.lpszClassName, TEXT("窓"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 450, NULL,
                        NULL, hInst, NULL);
}
INT_PTR CALLBACK AboutDialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_COMMAND: {
            WORD id = LOWORD(wParam);
            switch (id) {
                case IDOK:
                case IDCANCEL: {
                    EndDialog(hwndDlg, (INT_PTR)id);
                    return (INT_PTR)TRUE;
                }
            }
            break;
        }

        case WM_INITDIALOG: {
            return (INT_PTR)TRUE;
        }
    }

    return (INT_PTR)FALSE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
        case WM_COMMAND: {
            WORD id = LOWORD(wp);
            switch (id) {
                case ID_HELP_ABOUT: {
                    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTDIALOG), hWnd, &AboutDialogProc);
                    return 0;
                }
                case ID_FILE_EXIT: {
                    DestroyWindow(hWnd);
                    return 0;
                }
                case IDM_CLOSE: {
                    DestroyWindow(hWnd);
                    return 0;
                }
            }

        } break;

        case WM_RBUTTONUP: {
            POINT pt;
            pt.x = LOWORD(lp);
            pt.y = HIWORD(lp);
            ClientToScreen(hWnd, &pt);
            HMENU hMenu  = LoadMenu(NULL, MAKEINTRESOURCE(IDR_POPUPMENU));
            HMENU hMsenu = GetSubMenu(hMenu, 0);
            TrackPopupMenu(hMsenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);

        } break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC         hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        } break;

        case WM_SIZE: {
            if (wp == SIZE_MINIMIZED) {
            }
        } break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default: {
            return DefWindowProc(hWnd, msg, wp, lp);
        }
    }
    return 0;
}

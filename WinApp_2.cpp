// WinApp_2.cpp : Defines the entry point for the application.
//I will be entirely honest, I am not sure where this program is going. that being said it's going somewhere.

//also I am most certainly reinventing the wheel here. why? to understand how wheels work.

#define WIN32_LEAN_AND_MEAN

#include <wchar.h>
#include "pch.h"
#include "framework.h"
#include "WinApp_2.h"
#include <d2d1.h>
#include <windowsx.h>
#include "Graphics.h"
#include "Entity.h"
#include "Npc.h"
#include "Player.h"
#include "Mouse.h"



#define MAINWINDOW_WIDTH 600
#define MAINWINDOW_HEIGHT 600
#define MAX_LOADSTRING 100
#define CONNECT_OPTION 1
#define HOST_OPTION 2

// Global Variables:
HINSTANCE hInst;                                        // current instance
WCHAR szTitle[MAX_LOADSTRING] = L"WinAppDemo";                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING] = L"Main";            // the main window class name
WCHAR szDialogClass[MAX_LOADSTRING] = L"DialogConnect";
WCHAR szDialogTitle[MAX_LOADSTRING] = L"Connect";
HMENU hMenu;
Graphics* graphics;                                     // global graphics object
HWND connect;                                           // the following are used in connect
    HWND connect_info;
    HWND connect_IDBox;
    HWND connect_ok;
    HWND connect_cancel;
// Forward declarations of functions included in this code module:
ATOM                RegisterMain(HINSTANCE hInstance);
ATOM                RegisterDialog(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DlgProcConnect(HWND, UINT, WPARAM, LPARAM);
void                AddMenus(HWND hWnd);

Player* player = new Player(300, 300);
Npc* enemy = new Npc(0, 0, player, true);
Mouse* mouse = new Mouse();
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //LPWSTR is a const long string pointer.
    //HINSTANCE is the handle to an instance/module.
    //OS uses hInstance to identify the .exe file. windows functions that load icons or bitmaps also use this.
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPP2, szWindowClass, MAX_LOADSTRING);
    RegisterMain(hInstance);
    RegisterDialog(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//
//  FUNCTION: RegisterMain()
//
//  PURPOSE: Registers the main window class.
//
ATOM RegisterMain(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = DLGWINDOWEXTRA;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPP2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPP2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM RegisterDialog(HINSTANCE hInstance) {
    WNDCLASSEXW DlgWC;

    DlgWC.cbSize = sizeof(WNDCLASSEX);

    DlgWC.style = CS_HREDRAW | CS_VREDRAW;
    DlgWC.lpfnWndProc = DlgProcConnect;
    DlgWC.cbClsExtra = 0;
    DlgWC.cbWndExtra = 0;
    DlgWC.hInstance = hInstance;
    DlgWC.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPP2));
    DlgWC.hCursor = LoadCursor(nullptr, IDC_ARROW);
    DlgWC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    DlgWC.lpszMenuName = NULL;
    DlgWC.lpszClassName = szDialogClass;
    DlgWC.hIconSm = LoadIcon(DlgWC.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    
    return RegisterClassExW(&DlgWC);
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   graphics = new Graphics();
   if (!graphics->Init(hWnd)) {
       delete graphics;
       return -1;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //NOTE: The code for case WM_KEYDOWN is working (it is recieving the inputs) but now I need to figure out exactly how I intend for the program to use any of that.
    switch (message)
    {
    case WM_COMMAND:
        switch (wParam) {
        case HOST_OPTION:
            break;
        case CONNECT_OPTION:
            if (!IsWindow(connect)) {
                MessageBeep(MB_OK);
                connect = CreateWindow(szDialogClass, szDialogTitle, WS_DLGFRAME | WS_VISIBLE, 300, 300, 150, 200, hWnd, NULL, NULL, NULL);

            }
            break;
        }
        break;  
    case WM_CREATE:
        AddMenus(hWnd);
    case WM_SIZE:
        delete graphics;
        graphics = new Graphics();
        graphics->Init(hWnd);
        break;
    case WM_PAINT:
        COLLISION_DATA collision = player->CheckEntityCollision(enemy);
        player->DoCollisionLogic(collision);
        enemy->DoCollisionLogic(collision);
        player->AttemptMovement();
        player->lookAt(mouse->getX(), mouse->getY());
        enemy->Movement();
        graphics->BeginDraw();
        graphics->ClearScreen(0.0f, 0.0f, 0.5f);
        player->Render(graphics);
        enemy->Render(graphics);
        
        graphics->EndDraw();
        break;
    case WM_MOUSEMOVE:
        mouse->setX(GET_X_LPARAM(lParam));
        mouse->setY(GET_Y_LPARAM(lParam));
        player->lookAt(mouse->getX(), mouse->getY());
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case 0x57:
        case 0x53:
        case 0x41:
        case 0x44:
            player->MovementInput(true, wParam);
            break;
        case 0x43:
            
            break;
        }
        player->lookAt(mouse->getX(), mouse->getY());
        break;
    case WM_KEYUP:
        switch (wParam) {
        case 0x57:
        case 0x53:
        case 0x41:
        case 0x44:
            player->MovementInput(false, wParam);
            break;
        }
        player->lookAt(mouse->getX(), mouse->getY());
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK DlgProcConnect(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        connect_info = CreateWindow(L"static", L"Enter Session ID", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 135, 20, hWnd, NULL, NULL, NULL);
        connect_IDBox = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, 0, 20, 135, 50, hWnd, NULL, NULL, NULL);
        connect_ok = CreateWindow(L"button", L"Ok", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 70, 135, 30, hWnd, NULL, NULL, NULL);
        connect_cancel = CreateWindow(L"button", L"Cancel", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 100, 135, 30, hWnd, NULL, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case BN_CLICKED:
            if ((HWND)lParam == connect_cancel) {
                DestroyWindow(hWnd);
            }
            else if ((HWND)lParam == connect_ok) {
                WCHAR text[100];
                GetWindowText(connect_IDBox, text, 100);
                //TODO: set up socket class. this is where socket class will become relevant.
                
                /*
                if (false) {                    //Sockets will return a value here when a connection is successfully established.
                    int mBResponseSuccess = MessageBox(hWnd, L"Connection was successfully established :)", L"Connection Succeeded", MB_ICONASTERISK | MB_OK | WS_VISIBLE);
                }
                else {
                    int mBResponseFail = MessageBox(hWnd, L"Connection wasn't able to be established :(", L"Connection Failed", MB_ICONWARNING | MB_RETRYCANCEL | MB_DEFBUTTON2 | WS_VISIBLE);
                }
                */
            }
        }
        break;
    case WM_DESTROY:
        DestroyWindow(connect_info);
        DestroyWindow(connect_IDBox);
        DestroyWindow(connect_ok);
        DestroyWindow(connect_cancel);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
// Message handler for about box.
void AddMenus(HWND hWnd) {
    hMenu = CreateMenu();
    HMENU onlineMenu = CreateMenu();
    HMENU multiplayerMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)onlineMenu, L"Online");
    AppendMenu(onlineMenu, MF_POPUP, (UINT_PTR)multiplayerMenu, L"Multiplayer");
    AppendMenu(multiplayerMenu, MF_STRING, HOST_OPTION, L"Host");
    AppendMenu(multiplayerMenu, MF_STRING, CONNECT_OPTION, L"Connect");

    SetMenu(hWnd, hMenu);
}
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>

// Stuff required for Windows classes
const wchar_t* CLASS_NAME = L"Box Delivery Window Class";
const wchar_t* TITLEBAR = L"Box Delivery - alpha development stage.";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
  // Welcome message
  std::cout << "Welcome to Box Delivery - early alpha development engine!" << std::endl;

  // Entry here - preparing windows class and all that jazz
  WNDCLASS wc = {};

  // TODO: check this stuff and explain it here
  wc.lpfnWndProc = WindowProc; // Here goes function that has switch for all messages inside it
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Creating the window
  HWND hwnd = CreateWindowEx(
    0,          // Optional window styles.
    CLASS_NAME, // Window class
    TITLEBAR,   // Window text - at the top bar I guess
    WS_OVERLAPPEDWINDOW, // Window style
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and position
    NULL, // Parent window
    NULL, // Menu
    hInstance, // Instance handle - whatever that is TODO read more
    NULL // Additional data of application
  );
  // There are a lot more options to choose from, but right now we don't care, just give me a window

  if (hwnd == NULL) {
    return 0; // If it fails
  }

  ShowWindow(hwnd, nCmdShow);

  // Message loop - very important in Windows TODO read more
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // End message - if all went well
  std::cout << "All went well, goodbye..." << std::endl;
  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  // Switch for message loop
  // All cases here return 0, if not we return DefWindowProc
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_PAINT:
      {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All paiting occurs here, between BeginPaint and EndPaint
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1)); // TODO check what does COLOR_WINDOW doing here and what does it mean
        EndPaint(hwnd, &ps);
      }
      return 0;
  }

  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// This is entry point for subsystem console to have std cout enabled for console with all the goodness of windows application
// like the windows
int main(int argc, char* argv[]) {
  // Voiding argc and argv, we do not use them for now (maybe ever)
  (void) argc;
  (void) argv;

  return wWinMain(GetModuleHandle(NULL), NULL, (LPWSTR) GetCommandLineA(), SW_SHOWNORMAL);
}


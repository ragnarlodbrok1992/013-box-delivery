#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
  // Welcome message
  std::cout << "Welcome to Box Delivery - early alpha development engine!" << std::endl;

  // End message - if all went well
  std::cout << "All went well, goodbye..." << std::endl;
  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  
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

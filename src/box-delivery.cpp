#ifndef UNICODE
#define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// System headers
#include <windows.h>
#include <stdio.h>
#include <shellapi.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <d3d12.h>

// Compiler headers from C++ std thanks Barney
#include <iostream>
#include <string>
#include <stdexcept>

// TODO: rewrite whole application using debug session for hellotriangle sample

// TODO task 1: create BaseApplication class (same as DXSample class)
// TODO task 2: Check resources used in D3D12HelloTriangle class which inherits stuff from BaseApplication (DXSample class)
// TODO rewrite this stuff to be more sane than it is in MS tutorial, because it really sucks as a tutorial

// Declare all variables statically here for now
// TODO: get some common resolutions and put them somewhere
static UINT WINDOW_WIDTH = 1024;
static UINT WINDOW_HEIGHT = 768;
static std::wstring TITLE = L"Box Delivery"; // Windows strings require L before literal
static UINT FRAME_INDEX = 0; // I think here we are counting frames
static HWND M_HWND = nullptr;
static WNDCLASSEX WINDOW_CLASS = {0};

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
  // Print welcome message to console on Windows subsystem
  // This requires attaching to ParentProcessConsole
  if (AttachConsole(ATTACH_PARENT_PROCESS)) {
    // Redirect standard output to console
    freopen("CONOUT$", "w",  stdout);
    freopen("CONIN$", "r", stdin);

    printf("Hello, Box Delivery!\n");
  } else {
    MessageBox(NULL, L"Failed to attach console", L"Error", MB_OK);
  }

  // Parsing command line options - not used for now
  int argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  for (int x = 1; x < argc; ++x) { // Ommiting name of binary
    printf("Supplied %d command --> %ls\n", argc, argv[x]);
  }
  LocalFree(argv);
  
  // Intialize the window class
  WINDOW_CLASS.cbSize = sizeof(WNDCLASSEX);
  WINDOW_CLASS.style = CS_HREDRAW | CS_VREDRAW;
  WINDOW_CLASS.lpfnWndProc = WindowProc;
  WINDOW_CLASS.hInstance = hInstance;
  WINDOW_CLASS.hCursor = LoadCursor(NULL, IDC_ARROW); // Changing cursor for the game here?
  WINDOW_CLASS.lpszClassName = TITLE.c_str();
  RegisterClassEx(&WINDOW_CLASS);

  // Print exit message to console on Windows subsystem
  printf("All went well, goodbye...\n");
  return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE:
      {

      }
      return 0;
    case WM_PAINT:
      {

      }
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    default:
      return 0;
  }
}

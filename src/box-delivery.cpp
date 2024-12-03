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

// Compiler headers from C++ std thanks Barney
#include <iostream>
#include <string>
#include <stdexcept>

// Local submodule includes - directx headers helpers
#include "directx/d3d12.h"
#include "directx/d3dx12.h"

// TODO: rewrite whole application using debug session for hellotriangle sample

// Declare all variables statically here for now
// TODO: get some common resolutions and put them somewhere
static UINT WINDOW_WIDTH = 1024;
static UINT WINDOW_HEIGHT = 768;
static std::wstring TITLE = L"Box Delivery"; // Windows strings require L before literal
static UINT FRAME_INDEX = 0; // I think here we are counting frames
static HWND M_HWND = nullptr;
static WNDCLASSEX WINDOW_CLASS = {0};

// TODO: prepare pipeline objects from D3D1211on12.h as static objects for our executable

// Pipeline objects
static CD3DX12_VIEWPORT m_viewport;
static CD3DX12_RECT m_scissorRect;

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
  // Print welcome message to console on Windows subsystem
  // This requires attaching to ParentProcessConsole
#if 0 // Disabled for now - we cannot run in debuger if we do this - on subsystem console we don't have to, but binary will start console window, maybe we don't need that when shipping?
  if (AttachConsole(ATTACH_PARENT_PROCESS)) {
    // Redirect standard output to console
    freopen("CONOUT$", "w",  stdout);
    freopen("CONIN$", "r", stdin);

    printf("Hello, Box Delivery!\n");
  } else {
    MessageBox(NULL, L"Failed to attach console", L"Error", MB_OK);
    return 1;
  }
#endif

  // Print welcome message
  printf("Hello, Box Delivery!\n");

  // Parsing command line options - not used for now
  int argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  for (int x = 1; x < argc; ++x) { // Ommiting name of binary
    // printf("Supplied %d command --> %ls\n", argc, argv[x]); // We shouldn't printf to console?
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

  RECT windowRect = {0, 0, static_cast<LONG>(WINDOW_WIDTH), static_cast<LONG>(WINDOW_HEIGHT)};
  AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

  // Create window and store a handle to it
  M_HWND = CreateWindow(
      WINDOW_CLASS.lpszClassName,
      TITLE.c_str(),
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      windowRect.right - windowRect.left,
      windowRect.bottom - windowRect.top,
      nullptr, // No parent window
      nullptr, // No menus
      hInstance,
      nullptr); // lparam

  // Show window and run main event loop for windows messages
  ShowWindow(M_HWND, nCmdShow);

  // TODO: - next steps - go to pSample->OnInit and see what is going on there --> loadPipeline and loadAssets

  MSG msg = {};
  while (msg.message != WM_QUIT) {
    // Process any messages in the queue
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

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
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

int main(int argc, char* argv[]) {
  // Voiding them, since we don't use them here for now (maybe ever)
  (void) argc;
  (void) argv;

  return WinMain(GetModuleHandle(NULL), NULL, (LPSTR) GetCommandLineA(), SW_SHOWNORMAL);
}

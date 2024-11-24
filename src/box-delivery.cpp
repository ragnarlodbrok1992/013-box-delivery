#ifndef UNICODE
#define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// System headers
#include <windows.h>
#include <stdio.h>
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

  // Print exit message to console on Windows subsystem
  printf("All went well, goodbye...\n");
  return 0;
}

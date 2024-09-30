#ifndef UNICODE
#define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// System headers
#include <windows.h>
#include <wrl.h>
#include <dxgi1_6.h>
#include <d3d12.h>

// Compiler headers from C++ std thanks Barney
#include <iostream>
#include <string>
#include <stdexcept>

// After includes comes global setup variables for this file
// Stuff required for Windows classes
const wchar_t* CLASS_NAME = L"Box Delivery Window Class";
const wchar_t* TITLEBAR = L"Box Delivery - alpha development stage.";

// Graphics (DirectX) stuff
typedef struct {
  UINT m_width;
  UINT m_height;
  float m_aspectRatio;
} ViewportDimensions;

// Graphics (DirectX) forward declarations
void GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter);

// Some DirectX variables
static bool m_useWarpDevice = true;
static Microsoft::WRL::ComPtr<ID3D12Device> m_device;


// Shaders in std::string format
const std::string vertex_shader = R"()"; // Empty for now - using one big basic default shader TODO create my own
const std::string pixel_shader = R"()";  // Empty for now - see above

// Default shader from DirectX Graphics Sample
const std::string default_directx_shader = R"(
struct PSInput {
  float4 position : SV_POSITION;
  float4 color : COLOR;
};

PSInput VSMain(float4 position : POSITION, float4 color : COLOR) {
  PSInput result;

  result.position = position;
  result.color = color;

  return result;
}

float4 PSMain(PSInput input) : SV_TARGET {
  return input.color;
}
)";

// Taken from HelloTriangle sample
// 1. class HrException
// 2. ThrowIfFailed
// 3. HrToString() procedure
// TODO: push this out of class and exceptions when you get some knowledge about DirectX3D
inline std::string HrToString(HRESULT hr);

class HrException : public std::runtime_error {
  public:
    HrException(HRESULT hr) : std::runtime_error(HrToString(hr)), m_hr(hr) {}
    HRESULT Error() const { return m_hr; }
  private:
    const HRESULT m_hr;
};

inline void ThrowIfFailed(HRESULT hr) {
  if (FAILED(hr)) {
    throw HrException(hr);
  }
}

inline std::string HrToString(HRESULT hr) {
  char s_str[64] = {};
  sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<UINT>(hr));
  return std::string(s_str);
}

void initialize() {
  UINT dxgiFactoryFlags = 0;

  // DEBUG enabling
  // for now disabled
#if 0

#if defined(_DEBUG)
  {
    Microsoft::WRL::ComPtr<ID3D12Debug> debugController;

    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
      debugController->EnableDebugLayer();

      // Enable additional debug layers (how many are there????)
      dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
    }
  }
#endif

#endif

  // Not setting up debug layers anymore

  Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
  ThrowIfFailed(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)));

  if (m_useWarpDevice) {
    Microsoft::WRL::ComPtr<IDXGIAdapter> warpAdapter;
    ThrowIfFailed(factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));

    ThrowIfFailed(D3D12CreateDevice(
      warpAdapter.Get(),
      D3D_FEATURE_LEVEL_11_0,
      IID_PPV_ARGS(&m_device)
      ));
  } else {
    Microsoft::WRL::ComPtr<IDXGIAdapter1> hardwareAdapter;
    GetHardwareAdapter(factory.Get(), &hardwareAdapter, false); // TODO requestHighPerformanceAdapter is set to false

    ThrowIfFailed(D3D12CreateDevice(
      hardwareAdapter.Get(),
      D3D_FEATURE_LEVEL_11_0,
      IID_PPV_ARGS(&m_device)
      ));
  }

  // Describe and create the command queue.

  // Describe and create the swap chain.
  
  // This sample does not support fullscreen transitions TODO learn what it is actually

  // Create descriptor heaps.

  // Create frame resources.
}

void load_assets() {

}

// Helper functions from DXSample.cpp

void GetHardwareAdapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter, bool requestHighPerformanceAdapter) {
  *ppAdapter = nullptr; // Setting as null at the start - common practice I think

  Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
  Microsoft::WRL::ComPtr<IDXGIFactory6> factory6;

  // TODO check what is going on here under the hood - some IID_PPV_ARGS whatever that means boi I'm stupid
  if (SUCCEEDED(factory6->QueryInterface(IID_PPV_ARGS(&factory6)))) { // RECORD - four closing parenthesis!!!!
    for (UINT adapterIndex = 0;
         SUCCEEDED(factory6->EnumAdapterByGpuPreference(
             adapterIndex,
             requestHighPerformanceAdapter == true ? DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE : DXGI_GPU_PREFERENCE_UNSPECIFIED,
             IID_PPV_ARGS(&adapter)));
         ++adapterIndex) {
      DXGI_ADAPTER_DESC1 desc;
      adapter->GetDesc1(&desc);

      if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        // Don't select the Basic Render Driver adapter which I guess is software adapter run on CPU - not for us
        // we have power!!!!
        continue;
      }

      // Device that supports Direct3D 12 found, not creating device yet.
      if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
        break;
      }

    } // inner for
  } // for

  // Is this run again of no adapter was found? But the code is the same???
  if (adapter.Get() == nullptr) {
    for (UINT adapterIndex = 0; SUCCEEDED(pFactory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex) {
      DXGI_ADAPTER_DESC1 desc;
      adapter->GetDesc1(&desc);

      if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
        // This is the same code as above? wtf
        // This part uses pFactory->EnumAdapters1
        // and the above part uses factory6->EnumAdapterByGpuPreference
        // TODO optimze this when you have understanding of what is going on
        continue;
      }

      if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
        break;
      }
    }
  }

  *ppAdapter = adapter.Detach();
}

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

  // Stuff from OnInit in D3D12HelloTriangle - LoadPipeline and LoadAssets
  // TODO for now only assets would be data for triangle?
  // Load the rendering pipeline dependencies
  void initialize();
  void load_pipeline();

  ShowWindow(hwnd, nCmdShow);

  // DEBUG CODE FOR SIMPLE DEVELOPMENT TESTS
  // TODO check this after writing initialize and load_pipeline functions
#if 0

  IDXGIFactory1* testFactory = nullptr;
  IDXGIAdapter1** testAdapter = nullptr;
  bool request_high_performance_yes = true;
  bool request_high_performance_no = false;

  std::cout << "testFactory before: " << testFactory << std::endl;
  std::cout << "testAdapter before: " << testAdapter << std::endl;

  // FIXME it crushes here, gg ez
  GetHardwareAdapter(testFactory, testAdapter, request_high_performance_yes);

  std::cout << "testFactory after: " << testFactory << std::endl;
  std::cout << "testAdapter after: " << testAdapter << std::endl;

  // DEBUG code

#endif

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


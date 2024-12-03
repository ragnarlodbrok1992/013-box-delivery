@echo off
SET compiler_dir="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.41.34120\bin\Hostx64\x64\cl.exe"

REM Remember that we are building from "build" directory, so go one below that
SET directx_headers_include_dir="..\DirectX-Headers\include"
SET directx_headrs_lib_dir="..\DirectX-Headers"


IF NOT EXIST build mkdir build

pushd build

REM Compiling
REM  /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\ucrt\x64"^
REM  /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22621.0\um\x64"^

%compiler_dir% /EHsc /Zi /MDd^
  /DEBUG:FULL^
  /INCREMENT:NO^
  /std:c++17^
  /Fe:"box-delivery"^
  ../src/box-delivery.cpp^
  /I%directx_headers_include_dir%^
  /link User32.lib d3d12.lib DXGI.lib Shell32.lib^
  /SUBSYSTEM:CONSOLE

popd

@echo off
SET compiler_dir="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.40.33807\bin\Hostx64\x64\cl.exe"

IF NOT EXIST build mkdir build

pushd build

REM Compiling

%compiler_dir% /EHsc /Zi /MDd^
  /DEBUG:FULL^
  /INCREMENT:NO^
  /std:c++17^
  /Fe:"box-delivery"^
  ../src/box-delivery.cpp^
  /link User32.lib

popd

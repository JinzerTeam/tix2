@echo off

rem Cook to Cooked/Windows directory

set CurrPath=%CD%
set BinaryPath=%CurrPath%\..\..\..\Binary\Windows
set path=%path%;%BinaryPath%
set Converter=%BinaryPath%\02.ResConverter.exe

if not exist "Cooked" (
	mkdir Cooked
	pushd "Cooked"
	if not exist "Windows" (
		mkdir "Windows"
	)
	popd
)

echo Converting tjs files.
for %%i in (*.tjs) do (
echo converting - %%~i
%Converter% %%i Cooked\Windows\%%~ni.tasset
)

echo copy Config
pushd "Cooked\Windows"
if not exist "Config" (
	mkdir "Config"
)
popd
copy Config\*.ini Cooked\Windows\Config\

echo copy others data files
for %%i in (*.bn) do (
echo copying - %%i
copy %%i Cooked\Windows\%%i
)

pause
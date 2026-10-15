@echo off
setlocal
cd /d "%~dp0"
if not exist FacultyLeaveManagement.exe (
  echo Executable not found. Run build_windows.bat first.
  pause
  exit /b 1
)
FacultyLeaveManagement.exe
pause

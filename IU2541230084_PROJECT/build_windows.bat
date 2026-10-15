@echo off
setlocal
cd /d "%~dp0"
echo Building Faculty Leave Management...
g++ -std=c++17 -Wall -Wextra Source_Code\main.cpp Source_Code\Faculty.cpp Source_Code\Department.cpp Source_Code\LeaveRequest.cpp Source_Code\Approval.cpp Source_Code\LeaveSystem.cpp Source_Code\FileManager.cpp -o FacultyLeaveManagement.exe
if errorlevel 1 (
  echo.
  echo Build failed. Check that g++ is installed and available in PATH.
  pause
  exit /b 1
)
echo.
echo Build successful: FacultyLeaveManagement.exe
echo Run run_windows.bat to start the program.
pause

# Faculty Leave Management — CPP56

**Enrollment:** IU2541230084  
**Course level:** 2nd-year C++ / Object-Oriented Programming  
**Application type:** Console application, C++17

## Why this version is beginner-friendly

This version was intentionally rewritten to use concepts that can be explained in a 2nd-year viva: classes, private data, constructors, simple member functions, `for` loops, `if/else`, arrays, pointers, text files, and `try/catch`. It avoids smart pointers, vectors, lambdas, templates, `std::filesystem`, advanced array resizing, and complicated file-loading patterns.

The project still demonstrates the Blueprint requirements, including inheritance, runtime polymorphism, dynamic memory, validation, exception handling, and saving/loading records. Dynamic storage is implemented with arrays created using `new[]`; each array has a limit of 100 records and is released with `delete[]` in `LeaveSystem`'s destructor.

## Features

- Add and display faculty and department records.
- Search faculty, department, or leave request by ID.
- Update faculty information.
- Delete faculty or department records when doing so will not break a leave-request relationship.
- Apply for leave using real `YYYY-MM-DD` dates and calculate the inclusive number of days.
- Approve or reject pending leave requests and store an approval history.
- Print a report showing counts and approved leave days.
- Save records into plain-text files and reload them at startup.
- Validate IDs, duplicate records, dates, and menu choices.

## Project structure

```text
IU2541230084_PROJECT/
├── Source_Code/             # All C++ headers and source files
├── Data/                    # Created/updated text data files
├── UML/                     # 4 UML diagrams (PNG, DOT, PlantUML)
├── Screenshots/             # Screens captured from actual program runs
├── Tests/                   # Test runner, results, and logs
├── Documentation/           # Original supplied templates and Blueprint
├── .vscode/tasks.json       # VS Code build task
├── build_windows.bat        # Compile all .cpp files with MinGW g++
├── run_windows.bat          # Start the Windows executable
├── README.md
├── LEARNING_AND_VIVA_GUIDE.md
├── CODER_PROFILE_AND_DESIGN_CHOICES.md
└── SUBMISSION_CHECKLIST.md
```

## Required software

- Windows 10/11
- Visual Studio Code
- A C++ compiler with `g++` available in the terminal (MinGW-w64 / MSYS2 is a common choice)
- Python 3 is only needed to run the optional test runner

## Build on Windows

1. Extract the ZIP into a new folder.
2. Open the outer `IU2541230084_PROJECT` folder in VS Code.
3. Open **Terminal → New Terminal** and check `g++ --version` works.
4. Run:

```powershell
.\build_windows.bat
```

5. After it says `Build successful`, run:

```powershell
.\run_windows.bat
```

You can also compile manually from the project root:

```powershell
g++ -std=c++17 -Wall -Wextra Source_Code\main.cpp Source_Code\Faculty.cpp Source_Code\Department.cpp Source_Code\LeaveRequest.cpp Source_Code\Approval.cpp Source_Code\LeaveSystem.cpp Source_Code\FileManager.cpp -o FacultyLeaveManagement.exe
```

**Important:** Run the executable from the outer project folder, not from inside `Source_Code`, because the data files are stored in `Data/` relative to the working directory.

## Menu

1. Add Record (faculty or department)
2. Display Records
3. Search Record
4. Update Record (faculty)
5. Delete Record (faculty or department)
6. Main Transaction / Process (apply leave or approve/reject)
7. Report
8. Save / Load
9. Exit

Add a department before adding faculty. Faculty records use the department name. Add a faculty record before applying for leave.

## File handling

The program uses four simple text files, one record per line. Fields are separated by `|`:

- `Data/faculty.txt`: `facultyId|name|department`
- `Data/departments.txt`: `departmentId|departmentName`
- `Data/leave_requests.txt`: `requestId|facultyId|type|fromDate|toDate|status`
- `Data/approvals.txt`: `approvalId|requestId|managerId|status`

Do not type the `|` character inside names or leave types. Missing data files on the first run are treated as empty. The program saves records on exit; choose option 8 to save earlier. To verify persistence, exit and restart, then display the records/report.

## Concepts and where to find them

- **Encapsulation:** each record class keeps its data members `private` and provides public functions.
- **Constructors:** each record class has a default and a parameterized constructor.
- **Destructor:** `LeaveSystem::~LeaveSystem()` releases each dynamically allocated array with `delete[]`.
- **Inheritance:** `Faculty`, `Department`, `LeaveRequest`, and `Approval` inherit from `Displayable`.
- **Runtime polymorphism:** display functions call `display()` through a `Displayable*` pointer.
- **Dynamic memory:** `LeaveSystem` creates four arrays with `new[]`, each with capacity 100.
- **File handling:** `FileManager.cpp` saves and loads the four data files with `ofstream` and `ifstream`.
- **Validation and exceptions:** input, duplicate IDs, date ranges, and file errors are checked; `try/catch` reports an error rather than silently continuing.

## Testing

From the outer project folder, run:

```powershell
python Tests\run_tests.py
```

The script compiles the actual source files, runs the console application in clean temporary test folders, checks the expected messages, and tests saving/loading after a restart. `Tests/TEST_RESULTS.txt` and `Tests/TEST_LOGS.txt` record the results from the latest test run. The recorded automated run in this package passed 15/15 tests under GCC on Linux; **the Windows build still needs to be run on the target Windows/MinGW installation** before submission.

## Screenshots

`Screenshots/` contains console snapshots created from real runs of this program in the available test environment. They document the menu, adding records, applying for leave, and the report. If your faculty specifically requires screenshots from your own Windows system, run the application on Windows and replace/add those screenshots before submission.

## Limitations

- The project stores up to 100 records of each type.
- This is a console application with local text files; it is not connected to a database or network.
- It does not implement user login, encrypted data, email notifications, or a graphical interface.
- Leave dates are entered as `YYYY-MM-DD`.
- There is no concurrent/multi-user access.

## GitHub submission

A repository link has **not** been invented or marked as created. To create your real link:

1. Sign in to GitHub and create a repository named `IU2541230084_FacultyLeaveManagement`.
2. Upload the contents of this project folder (including `Source_Code`, `UML`, `Tests`, docs, and README). Do not commit personal/private information.
3. If Git is installed, from the project folder use the commands GitHub provides for an existing local folder; check that the repository URL opens in a private/incognito window or while signed out if it is meant to be public.
4. Replace `GITHUB_REPOSITORY_URL_TO_BE_ADDED` in the project documents with the actual repository URL.

**Before final submission:** run the Windows build, open the app, capture any required Windows screenshots, fill in the student name/date/signature, create and verify the actual GitHub URL, and upload the ZIP to the correct section-specific folder.

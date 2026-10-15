"""Beginner-friendly integration tests for Faculty Leave Management.
Run from the project folder with: python Tests/run_tests.py
The script compiles the C++ source and tests the real console program in temporary folders.
"""
import os
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCES = [
    "Source_Code/main.cpp",
    "Source_Code/Faculty.cpp",
    "Source_Code/Department.cpp",
    "Source_Code/LeaveRequest.cpp",
    "Source_Code/Approval.cpp",
    "Source_Code/LeaveSystem.cpp",
    "Source_Code/FileManager.cpp",
]
EXE = ROOT / ("FacultyLeaveManagement_test.exe" if os.name == "nt" else "FacultyLeaveManagement_test")


def compile_program():
    command = ["g++", "-std=c++17", "-Wall", "-Wextra"]
    command += [str(ROOT / name) for name in SOURCES]
    command += ["-o", str(EXE)]
    result = subprocess.run(command, capture_output=True, text=True)
    if result.returncode != 0:
        print(result.stdout)
        print(result.stderr)
        raise SystemExit("Compilation failed. Fix the source code before running tests.")


def run_case(test_id, title, input_lines, expected_text, second_run=False):
    with tempfile.TemporaryDirectory(prefix="faculty_leave_test_") as temp:
        work = Path(temp)
        (work / "Data").mkdir()
        process = subprocess.run(
            [str(EXE)], input="\n".join(str(x) for x in input_lines) + "\n",
            text=True, capture_output=True, cwd=work, timeout=10
        )
        output = process.stdout + process.stderr
        if second_run:
            again = subprocess.run(
                [str(EXE)], input="7\n2\n9\n", text=True,
                capture_output=True, cwd=work, timeout=10
            )
            output += "\n--- REOPENED APPLICATION ---\n" + again.stdout + again.stderr
        passed = process.returncode == 0 and all(word in output for word in expected_text)
        short_actual = " | ".join([line.strip() for line in output.splitlines() if any(
            marker.lower() in line.lower() for marker in [
                "added successfully", "display", "not found", "updated successfully",
                "deleted.", "Duration:", "not created", "Approved", "Rejected",
                "already exists", "Cannot delete", "Faculty members:", "Invalid menu choice",
                "Departments:", "Leave requests:", "Records saved", "Goodbye"
            ])])
        if not short_actual:
            short_actual = "Program finished; expected text checked in captured output."
        return {
            "id": test_id,
            "title": title,
            "passed": passed,
            "expected": "; ".join(expected_text),
            "actual": short_actual,
            "output": output,
        }


def main():
    compile_program()
    tests = [
        ("T01", "Add Department", [1, 2, 1, "Computer Science", 9], ["Department record added successfully."]),
        ("T02", "Add Faculty", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 9], ["Faculty record added successfully."]),
        ("T03", "Display saved records in current session", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 2, 9], ["Faculty ID: 101", "Yash Gupta"]),
        ("T04", "Search existing faculty", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 3, 1, 101, 9], ["Faculty ID: 101", "Yash Gupta"]),
        ("T05", "Search missing faculty", [3, 1, 999, 9], ["Faculty record not found."]),
        ("T06", "Update faculty record", [1, 2, 1, "Computer Science", 1, 2, 2, "Information Technology", 1, 1, 101, "Yash Gupta", "Computer Science", 4, 101, "Yash Updated", "Information Technology", 2, 9], ["Faculty record updated successfully.", "Yash Updated"]),
        ("T07", "Delete faculty without request history", [1, 2, 1, "Physics", 1, 1, 101, "Demo Faculty", "Physics", 5, 1, 101, 2, 9], ["Faculty record deleted."]),
        ("T08", "Apply valid leave and calculate duration", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-20", "2026-10-22", 9], ["Leave request submitted.", "Duration: 3 day(s)."]),
        ("T09", "Reject an invalid date range", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-22", "2026-10-20", 9], ["Leave request not created:", "End date cannot be before start date."]),
        ("T10", "Approve a pending leave request", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-20", "2026-10-22", 6, 2, 1, 1, 900, 7, 9], ["Leave request Approved.", "Approved: 1"]),
        ("T11", "Reject a pending leave request", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-20", "2026-10-22", 6, 2, 1, 2, 900, 7, 9], ["Leave request Rejected.", "Rejected: 1"]),
        ("T12", "Reject duplicate faculty ID", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 1, 1, 101, "Other Faculty", "Computer Science", 9], ["This Faculty ID already exists."]),
        ("T13", "Protect faculty with leave-request history", [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-20", "2026-10-22", 5, 1, 101, 9], ["Cannot delete faculty with leave-request history."]),
    ]
    results = []
    for test in tests:
        results.append(run_case(*test))

    # Persistence: first process writes files on exit, a fresh process loads those files.
    with tempfile.TemporaryDirectory(prefix="faculty_leave_persist_") as temp:
        work = Path(temp)
        (work / "Data").mkdir()
        first_input = [1, 2, 1, "Computer Science", 1, 1, 101, "Yash Gupta", "Computer Science", 6, 1, 101, "Sick", "2026-10-20", "2026-10-22", 6, 2, 1, 1, 900, 9]
        first = subprocess.run([str(EXE)], input="\n".join(map(str, first_input))+"\n", text=True, capture_output=True, cwd=work, timeout=10)
        second = subprocess.run([str(EXE)], input="2\n7\n9\n", text=True, capture_output=True, cwd=work, timeout=10)
        output = first.stdout + "\n--- REOPENED APPLICATION ---\n" + second.stdout
        passed = first.returncode == 0 and second.returncode == 0 and "Yash Gupta" in output and "Approved: 1" in output
        results.append({"id":"T14","title":"Save and load records after restart","passed":passed,"expected":"Faculty and approved request remain after closing and reopening","actual":"; ".join(line.strip() for line in output.splitlines() if "Yash Gupta" in line or "Approved:" in line or "Records saved" in line),"output":output})

    results.append(run_case("T15", "Invalid menu choice", [77, 9], ["Invalid menu choice. Enter 1 to 9."]))

    outdir = ROOT / "Tests"
    lines = ["FACULTY LEAVE MANAGEMENT - AUTOMATED TEST RESULTS", "Compiler: g++ -std=c++17", "Test environment: Linux integration run", ""]
    for result in results:
        lines.append(f"{result['id']} - {result['title']}: {'PASS' if result['passed'] else 'FAIL'}")
        lines.append(f"  Expected: {result['expected']}")
        lines.append(f"  Actual: {result['actual']}")
        lines.append("")
    lines.append(f"TOTAL: {sum(1 for r in results if r['passed'])}/{len(results)} PASS")
    (outdir / "TEST_RESULTS.txt").write_text("\n".join(lines), encoding="utf-8")
    with (outdir / "TEST_LOGS.txt").open("w", encoding="utf-8") as handle:
        for result in results:
            handle.write(f"\n{'='*72}\n{result['id']} - {result['title']} - {'PASS' if result['passed'] else 'FAIL'}\n{'='*72}\n")
            handle.write(result["output"])
            handle.write("\n")
    print("\n".join(lines))
    if any(not result["passed"] for result in results):
        raise SystemExit(1)

if __name__ == "__main__":
    main()

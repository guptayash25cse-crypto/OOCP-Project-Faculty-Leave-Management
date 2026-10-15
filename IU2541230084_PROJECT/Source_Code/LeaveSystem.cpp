#include "LeaveSystem.h"
#include "FileManager.h"
#include <iostream>
#include <limits>
#include <stdexcept>

// Basic input helpers keep input validation out of the main operations.
int readNumber(std::string message) {
    int number;
    while (true) {
        std::cout << message;
        if (std::cin >> number) {
            std::cin.ignore(10000, '\n');
            return number;
        }
        std::cout << "Please enter a whole number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

std::string readText(std::string message) {
    std::string text;
    while (true) {
        std::cout << message;
        std::getline(std::cin, text);
        if (text != "" && text.find('|') == std::string::npos) return text;
        std::cout << "Text cannot be empty or contain the | character. Try again.\n";
    }
}

LeaveSystem::LeaveSystem() {
    // Allocate arrays dynamically as required by the project blueprint.
    faculty = new Faculty[MAX_RECORDS];
    departments = new Department[MAX_RECORDS];
    requests = new LeaveRequest[MAX_RECORDS];
    approvals = new Approval[MAX_RECORDS];
    facultyCount = 0;
    departmentCount = 0;
    requestCount = 0;
    approvalCount = 0;
    nextRequestId = 1;
    nextApprovalId = 1;
}

LeaveSystem::~LeaveSystem() {
    delete[] faculty;
    delete[] departments;
    delete[] requests;
    delete[] approvals;
}

int LeaveSystem::findFaculty(int id) const {
    for (int i = 0; i < facultyCount; i++) {
        if (faculty[i].getId() == id) return i;
    }
    return -1;
}

int LeaveSystem::findDepartment(int id) const {
    for (int i = 0; i < departmentCount; i++) {
        if (departments[i].getId() == id) return i;
    }
    return -1;
}

int LeaveSystem::findRequest(int id) const {
    for (int i = 0; i < requestCount; i++) {
        if (requests[i].getId() == id) return i;
    }
    return -1;
}

bool LeaveSystem::departmentExists(std::string name) const {
    for (int i = 0; i < departmentCount; i++) {
        if (departments[i].getName() == name) return true;
    }
    return false;
}

void LeaveSystem::addFaculty() {
    if (facultyCount >= MAX_RECORDS) {
        std::cout << "Faculty storage is full.\n";
        return;
    }
    int id = readNumber("Enter Faculty ID: ");
    if (id <= 0) { std::cout << "ID must be positive.\n"; return; }
    if (findFaculty(id) != -1) { std::cout << "This Faculty ID already exists.\n"; return; }
    std::string name = readText("Enter Faculty Name: ");
    std::string department = readText("Enter Department Name (add department first): ");
    if (!departmentExists(department)) {
        std::cout << "Department was not found. Add the department first.\n";
        return;
    }
    faculty[facultyCount] = Faculty(id, name, department);
    facultyCount++;
    std::cout << "Faculty record added successfully.\n";
}

void LeaveSystem::addDepartment() {
    if (departmentCount >= MAX_RECORDS) {
        std::cout << "Department storage is full.\n";
        return;
    }
    int id = readNumber("Enter Department ID: ");
    if (id <= 0) { std::cout << "ID must be positive.\n"; return; }
    if (findDepartment(id) != -1) { std::cout << "This Department ID already exists.\n"; return; }
    std::string name = readText("Enter Department Name: ");
    if (departmentExists(name)) { std::cout << "This department already exists.\n"; return; }
    departments[departmentCount] = Department(id, name);
    departmentCount++;
    std::cout << "Department record added successfully.\n";
}

void LeaveSystem::addRecord() {
    std::cout << "\nAdd Record\n1. Add Faculty\n2. Add Department\n";
    int choice = readNumber("Choose record type: ");
    if (choice == 1) addFaculty();
    else if (choice == 2) addDepartment();
    else std::cout << "Invalid record type.\n";
}

void LeaveSystem::displayFaculty() const {
    std::cout << "\n--- Faculty Records ---\n";
    if (facultyCount == 0) std::cout << "No faculty records.\n";
    for (int i = 0; i < facultyCount; i++) {
        // A base-class pointer calls the matching derived display() function.
        Displayable* item = &faculty[i];
        item->display();
    }
}

void LeaveSystem::displayDepartments() const {
    std::cout << "\n--- Department Records ---\n";
    if (departmentCount == 0) std::cout << "No department records.\n";
    for (int i = 0; i < departmentCount; i++) {
        Displayable* item = &departments[i];
        item->display();
    }
}

void LeaveSystem::displayRequests() const {
    std::cout << "\n--- Leave Requests ---\n";
    if (requestCount == 0) std::cout << "No leave requests.\n";
    for (int i = 0; i < requestCount; i++) {
        Displayable* item = &requests[i];
        item->display();
    }
}

void LeaveSystem::displayApprovals() const {
    std::cout << "\n--- Approval History ---\n";
    if (approvalCount == 0) std::cout << "No approval history.\n";
    for (int i = 0; i < approvalCount; i++) {
        Displayable* item = &approvals[i];
        item->display();
    }
}

void LeaveSystem::displayRecords() const {
    displayDepartments();
    displayFaculty();
    displayRequests();
    displayApprovals();
}

void LeaveSystem::searchRecord() const {
    std::cout << "\nSearch Record\n1. Faculty\n2. Department\n3. Leave Request\n";
    int type = readNumber("Choose type: ");
    int id = readNumber("Enter ID: ");
    int index = -1;
    if (type == 1) {
        index = findFaculty(id);
        if (index >= 0) faculty[index].display();
        else std::cout << "Faculty record not found.\n";
    } else if (type == 2) {
        index = findDepartment(id);
        if (index >= 0) departments[index].display();
        else std::cout << "Department record not found.\n";
    } else if (type == 3) {
        index = findRequest(id);
        if (index >= 0) requests[index].display();
        else std::cout << "Leave request not found.\n";
    } else {
        std::cout << "Invalid search type.\n";
    }
}

void LeaveSystem::updateRecord() {
    int id = readNumber("Enter Faculty ID to update: ");
    int index = findFaculty(id);
    if (index == -1) { std::cout << "Faculty record not found.\n"; return; }
    std::string name = readText("Enter new name: ");
    std::string department = readText("Enter department name: ");
    if (!departmentExists(department)) {
        std::cout << "Department not found. Update cancelled.\n";
        return;
    }
    faculty[index].updateDetails(name, department);
    std::cout << "Faculty record updated successfully.\n";
}

void LeaveSystem::deleteRecord() {
    std::cout << "\nDelete Record\n1. Faculty\n2. Department\n";
    int type = readNumber("Choose type: ");
    int id = readNumber("Enter ID to delete: ");
    if (type == 1) {
        int index = findFaculty(id);
        if (index == -1) { std::cout << "Faculty record not found.\n"; return; }
        for (int i = 0; i < requestCount; i++) {
            if (requests[i].getFacultyId() == id) {
                std::cout << "Cannot delete faculty with leave-request history.\n";
                return;
            }
        }
        for (int i = index; i < facultyCount - 1; i++) faculty[i] = faculty[i + 1];
        facultyCount--;
        std::cout << "Faculty record deleted.\n";
    } else if (type == 2) {
        int index = findDepartment(id);
        if (index == -1) { std::cout << "Department record not found.\n"; return; }
        for (int i = 0; i < facultyCount; i++) {
            if (faculty[i].getDepartment() == departments[index].getName()) {
                std::cout << "Cannot delete a department used by faculty.\n";
                return;
            }
        }
        for (int i = index; i < departmentCount - 1; i++) departments[i] = departments[i + 1];
        departmentCount--;
        std::cout << "Department record deleted.\n";
    } else {
        std::cout << "Invalid record type.\n";
    }
}

void LeaveSystem::applyForLeave() {
    if (requestCount >= MAX_RECORDS) { std::cout << "Leave-request storage is full.\n"; return; }
    int facultyId = readNumber("Enter Faculty ID: ");
    if (findFaculty(facultyId) == -1) {
        std::cout << "Faculty not found. Add the faculty record first.\n";
        return;
    }
    std::string type = readText("Enter leave type (Casual/Sick/Earned): ");
    std::string from = readText("Enter start date (YYYY-MM-DD): ");
    std::string to = readText("Enter end date (YYYY-MM-DD): ");
    try {
        if (!LeaveRequest::isValidDate(from) || !LeaveRequest::isValidDate(to)) {
            throw std::invalid_argument("Enter real dates in YYYY-MM-DD format.");
        }
        if (LeaveRequest::dateNumber(to) < LeaveRequest::dateNumber(from)) {
            throw std::invalid_argument("End date cannot be before start date.");
        }
        requests[requestCount] = LeaveRequest(nextRequestId, facultyId, type, from, to, "Pending");
        std::cout << "Leave request submitted. Request ID: " << nextRequestId
                  << ". Duration: " << requests[requestCount].calculateDays() << " day(s).\n";
        requestCount++;
        nextRequestId++;
    } catch (const std::exception& error) {
        std::cout << "Leave request not created: " << error.what() << '\n';
    }
}

void LeaveSystem::decideLeave() {
    if (approvalCount >= MAX_RECORDS) { std::cout << "Approval storage is full.\n"; return; }
    int id = readNumber("Enter Leave Request ID: ");
    int index = findRequest(id);
    if (index == -1) { std::cout << "Leave request not found.\n"; return; }
    if (requests[index].getStatus() != "Pending") {
        std::cout << "This request has already been processed.\n";
        return;
    }
    int decision = readNumber("1. Approve  2. Reject: ");
    if (decision != 1 && decision != 2) { std::cout << "Invalid decision.\n"; return; }
    int managerId = readNumber("Enter Manager ID: ");
    Approval approval(nextApprovalId, id, managerId, "Pending");
    if (decision == 1) {
        approval.approve();
        requests[index].setStatus("Approved");
    } else {
        approval.reject();
        requests[index].setStatus("Rejected");
    }
    approvals[approvalCount] = approval;
    approvalCount++;
    nextApprovalId++;
    std::cout << "Leave request " << requests[index].getStatus() << ".\n";
}

void LeaveSystem::processTransaction() {
    std::cout << "\nMain Transaction / Process\n1. Apply for leave\n2. Approve or reject leave\n";
    int choice = readNumber("Choose process: ");
    if (choice == 1) applyForLeave();
    else if (choice == 2) decideLeave();
    else std::cout << "Invalid process choice.\n";
}

void LeaveSystem::report() const {
    int approved = 0;
    int rejected = 0;
    int pending = 0;
    int approvedDays = 0;
    for (int i = 0; i < requestCount; i++) {
        if (requests[i].getStatus() == "Approved") {
            approved++;
            approvedDays += requests[i].calculateDays();
        } else if (requests[i].getStatus() == "Rejected") rejected++;
        else pending++;
    }
    std::cout << "\n===== FACULTY LEAVE REPORT =====\n";
    std::cout << "Departments: " << departmentCount << '\n';
    std::cout << "Faculty members: " << facultyCount << '\n';
    std::cout << "Leave requests: " << requestCount << '\n';
    std::cout << "Pending: " << pending << '\n';
    std::cout << "Approved: " << approved << '\n';
    std::cout << "Rejected: " << rejected << '\n';
    std::cout << "Approved leave days: " << approvedDays << '\n';
    std::cout << "Approval decisions recorded: " << approvalCount << '\n';
}

void LeaveSystem::saveNow() const {
    FileManager manager;
    manager.save(*this);
    std::cout << "Records saved to the Data folder.\n";
}

void LeaveSystem::loadData() {
    FileManager manager;
    manager.load(*this);
    std::cout << "Saved records loaded. Missing files are treated as empty on the first run.\n";
}

void LeaveSystem::saveLoadMenu() {
    std::cout << "\nSave / Load\n1. Save records\n2. Load records (unsaved changes will be lost)\n";
    int choice = readNumber("Choose action: ");
    if (choice == 1) saveNow();
    else if (choice == 2) {
        int confirm = readNumber("Enter 1 to confirm, 2 to cancel: ");
        if (confirm == 1) loadData();
        else std::cout << "Load cancelled.\n";
    } else std::cout << "Invalid choice.\n";
}

void LeaveSystem::clearRecords() {
    facultyCount = 0;
    departmentCount = 0;
    requestCount = 0;
    approvalCount = 0;
    nextRequestId = 1;
    nextApprovalId = 1;
}

#include "FileManager.h"
#include "LeaveSystem.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

// Data files use one record per line and | between fields.
void FileManager::save(const LeaveSystem& system) const {
    std::ofstream facultyFile("Data/faculty.txt");
    std::ofstream departmentFile("Data/departments.txt");
    std::ofstream requestFile("Data/leave_requests.txt");
    std::ofstream approvalFile("Data/approvals.txt");

    if (!facultyFile || !departmentFile || !requestFile || !approvalFile) {
        throw std::runtime_error("Could not open files in Data. Run the program from the project folder.");
    }

    for (int i = 0; i < system.facultyCount; i++) {
        facultyFile << system.faculty[i].getId() << '|'
                    << system.faculty[i].getName() << '|'
                    << system.faculty[i].getDepartment() << '\n';
    }
    for (int i = 0; i < system.departmentCount; i++) {
        departmentFile << system.departments[i].getId() << '|'
                       << system.departments[i].getName() << '\n';
    }
    for (int i = 0; i < system.requestCount; i++) {
        requestFile << system.requests[i].getId() << '|'
                    << system.requests[i].getFacultyId() << '|'
                    << system.requests[i].getType() << '|'
                    << system.requests[i].getFromDate() << '|'
                    << system.requests[i].getToDate() << '|'
                    << system.requests[i].getStatus() << '\n';
    }
    for (int i = 0; i < system.approvalCount; i++) {
        approvalFile << system.approvals[i].getId() << '|'
                     << system.approvals[i].getRequestId() << '|'
                     << system.approvals[i].getManagerId() << '|'
                     << system.approvals[i].getStatus() << '\n';
    }
    if (!facultyFile || !departmentFile || !requestFile || !approvalFile) {
        throw std::runtime_error("A data file could not be written completely.");
    }
}

void FileManager::load(LeaveSystem& system) const {
    system.clearRecords();
    std::string line;

    std::ifstream facultyFile("Data/faculty.txt");
    while (std::getline(facultyFile, line)) {
        if (line == "") continue;
        std::stringstream row(line);
        std::string idText, name, department;
        if (!std::getline(row, idText, '|') || !std::getline(row, name, '|') || !std::getline(row, department))
            throw std::runtime_error("A row in faculty.txt is not formatted correctly.");
        if (system.facultyCount >= MAX_RECORDS) throw std::runtime_error("Too many faculty records in file.");
        int id = std::stoi(idText);
        if (system.findFaculty(id) != -1) throw std::runtime_error("Duplicate faculty ID in data file.");
        system.faculty[system.facultyCount] = Faculty(id, name, department);
        system.facultyCount++;
    }

    std::ifstream departmentFile("Data/departments.txt");
    while (std::getline(departmentFile, line)) {
        if (line == "") continue;
        std::stringstream row(line);
        std::string idText, name;
        if (!std::getline(row, idText, '|') || !std::getline(row, name))
            throw std::runtime_error("A row in departments.txt is not formatted correctly.");
        if (system.departmentCount >= MAX_RECORDS) throw std::runtime_error("Too many department records in file.");
        int id = std::stoi(idText);
        if (system.findDepartment(id) != -1 || system.departmentExists(name))
            throw std::runtime_error("Duplicate department in data file.");
        system.departments[system.departmentCount] = Department(id, name);
        system.departmentCount++;
    }

    std::ifstream requestFile("Data/leave_requests.txt");
    while (std::getline(requestFile, line)) {
        if (line == "") continue;
        std::stringstream row(line);
        std::string idText, facultyText, type, from, to, status;
        if (!std::getline(row, idText, '|') || !std::getline(row, facultyText, '|') ||
            !std::getline(row, type, '|') || !std::getline(row, from, '|') ||
            !std::getline(row, to, '|') || !std::getline(row, status))
            throw std::runtime_error("A row in leave_requests.txt is not formatted correctly.");
        if (system.requestCount >= MAX_RECORDS) throw std::runtime_error("Too many leave requests in file.");
        int id = std::stoi(idText);
        int facultyId = std::stoi(facultyText);
        if (system.findFaculty(facultyId) == -1) throw std::runtime_error("Leave request has a missing faculty record.");
        if (system.findRequest(id) != -1) throw std::runtime_error("Duplicate request ID in data file.");
        system.requests[system.requestCount] = LeaveRequest(id, facultyId, type, from, to, status);
        system.requestCount++;
        if (id >= system.nextRequestId) system.nextRequestId = id + 1;
    }

    std::ifstream approvalFile("Data/approvals.txt");
    while (std::getline(approvalFile, line)) {
        if (line == "") continue;
        std::stringstream row(line);
        std::string idText, requestText, managerText, status;
        if (!std::getline(row, idText, '|') || !std::getline(row, requestText, '|') ||
            !std::getline(row, managerText, '|') || !std::getline(row, status))
            throw std::runtime_error("A row in approvals.txt is not formatted correctly.");
        if (system.approvalCount >= MAX_RECORDS) throw std::runtime_error("Too many approvals in file.");
        int id = std::stoi(idText);
        int requestId = std::stoi(requestText);
        int managerId = std::stoi(managerText);
        if (system.findRequest(requestId) == -1) throw std::runtime_error("Approval has a missing leave request.");
        system.approvals[system.approvalCount] = Approval(id, requestId, managerId, status);
        system.approvalCount++;
        if (id >= system.nextApprovalId) system.nextApprovalId = id + 1;
    }
}

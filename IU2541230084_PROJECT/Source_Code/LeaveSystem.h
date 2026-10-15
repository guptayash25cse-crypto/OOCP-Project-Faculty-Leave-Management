#ifndef LEAVESYSTEM_H
#define LEAVESYSTEM_H

#include "Faculty.h"
#include "Department.h"
#include "LeaveRequest.h"
#include "Approval.h"

const int MAX_RECORDS = 100;

class FileManager;

class LeaveSystem {
private:
    Faculty* faculty;
    Department* departments;
    LeaveRequest* requests;
    Approval* approvals;
    int facultyCount;
    int departmentCount;
    int requestCount;
    int approvalCount;
    int nextRequestId;
    int nextApprovalId;

    int findFaculty(int id) const;
    int findDepartment(int id) const;
    int findRequest(int id) const;
    bool departmentExists(std::string name) const;
    void addFaculty();
    void addDepartment();
    void applyForLeave();
    void decideLeave();
    void displayFaculty() const;
    void displayDepartments() const;
    void displayRequests() const;
    void displayApprovals() const;
    void clearRecords();

    friend class FileManager;

public:
    LeaveSystem();
    ~LeaveSystem();

    void addRecord();
    void displayRecords() const;
    void searchRecord() const;
    void updateRecord();
    void deleteRecord();
    void processTransaction();
    void report() const;
    void saveNow() const;
    void loadData();
    void saveLoadMenu();
};

#endif

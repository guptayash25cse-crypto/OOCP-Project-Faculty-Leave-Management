#include "Approval.h"
#include <iostream>

Approval::Approval() {
    approvalId = 0;
    requestId = 0;
    managerId = 0;
    status = "Pending";
}

Approval::Approval(int id, int request, int manager, std::string decision) {
    approvalId = id;
    requestId = request;
    managerId = manager;
    status = decision;
}

int Approval::getId() const { return approvalId; }
int Approval::getRequestId() const { return requestId; }
int Approval::getManagerId() const { return managerId; }
std::string Approval::getStatus() const { return status; }
void Approval::approve() { status = "Approved"; }
void Approval::reject() { status = "Rejected"; }

void Approval::display() const {
    std::cout << "Approval ID: " << approvalId
              << " | Request ID: " << requestId
              << " | Manager ID: " << managerId
              << " | Status: " << status << '\n';
}

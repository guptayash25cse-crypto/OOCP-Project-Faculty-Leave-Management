#ifndef APPROVAL_H
#define APPROVAL_H

#include "Displayable.h"
#include <string>

class Approval : public Displayable {
private:
    int approvalId;
    int requestId;
    int managerId;
    std::string status;

public:
    Approval();
    Approval(int id, int request, int manager, std::string decision);

    int getId() const;
    int getRequestId() const;
    int getManagerId() const;
    std::string getStatus() const;
    void approve();
    void reject();
    void display() const override;
};

#endif

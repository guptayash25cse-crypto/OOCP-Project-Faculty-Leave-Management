#ifndef LEAVEREQUEST_H
#define LEAVEREQUEST_H

#include "Displayable.h"
#include <string>

class LeaveRequest : public Displayable {
private:
    int requestId;
    int facultyId;
    std::string type;
    std::string fromDate;
    std::string toDate;
    std::string status;

public:
    LeaveRequest();
    LeaveRequest(int id, int faculty, std::string leaveType,
                 std::string startDate, std::string endDate,
                 std::string requestStatus = "Pending");

    int getId() const;
    int getFacultyId() const;
    std::string getType() const;
    std::string getFromDate() const;
    std::string getToDate() const;
    std::string getStatus() const;
    void setStatus(std::string newStatus);
    int calculateDays() const;
    void display() const override;

    static bool isValidDate(std::string date);
    static int dateNumber(std::string date);
};

#endif

#include "LeaveRequest.h"
#include <iostream>
#include <stdexcept>

// Simple date helpers are kept here so the date rules are in one place.
int daysInMonth(int year, int month) {
    if (month == 2) {
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) return 29;
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
    if (month >= 1 && month <= 12) return 31;
    return 0;
}

LeaveRequest::LeaveRequest() {
    requestId = 0;
    facultyId = 0;
    type = "";
    fromDate = "";
    toDate = "";
    status = "Pending";
}

LeaveRequest::LeaveRequest(int id, int faculty, std::string leaveType,
                           std::string startDate, std::string endDate,
                           std::string requestStatus) {
    if (!isValidDate(startDate) || !isValidDate(endDate)) {
        throw std::invalid_argument("Dates must be real dates in YYYY-MM-DD format.");
    }
    if (dateNumber(endDate) < dateNumber(startDate)) {
        throw std::invalid_argument("End date cannot be before start date.");
    }
    requestId = id;
    facultyId = faculty;
    type = leaveType;
    fromDate = startDate;
    toDate = endDate;
    status = requestStatus;
}

int LeaveRequest::getId() const { return requestId; }
int LeaveRequest::getFacultyId() const { return facultyId; }
std::string LeaveRequest::getType() const { return type; }
std::string LeaveRequest::getFromDate() const { return fromDate; }
std::string LeaveRequest::getToDate() const { return toDate; }
std::string LeaveRequest::getStatus() const { return status; }

void LeaveRequest::setStatus(std::string newStatus) {
    if (newStatus != "Pending" && newStatus != "Approved" && newStatus != "Rejected") {
        throw std::invalid_argument("Status must be Pending, Approved, or Rejected.");
    }
    status = newStatus;
}

bool LeaveRequest::isValidDate(std::string date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (date[i] < '0' || date[i] > '9') return false;
    }
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    if (year < 1900 || year > 2200) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    return true;
}

int LeaveRequest::dateNumber(std::string date) {
    if (!isValidDate(date)) throw std::invalid_argument("Invalid date.");
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    int total = 0;
    // Count the days in all earlier years and months.
    for (int y = 1; y < year; y++) {
        if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) total += 366;
        else total += 365;
    }
    for (int m = 1; m < month; m++) total += daysInMonth(year, m);
    total += day;
    return total;
}

int LeaveRequest::calculateDays() const {
    return dateNumber(toDate) - dateNumber(fromDate) + 1;
}

void LeaveRequest::display() const {
    std::cout << "Request ID: " << requestId
              << " | Faculty ID: " << facultyId
              << " | Type: " << type
              << " | From: " << fromDate
              << " | To: " << toDate
              << " | Days: " << calculateDays()
              << " | Status: " << status << '\n';
}

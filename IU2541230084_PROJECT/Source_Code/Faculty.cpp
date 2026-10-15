#include "Faculty.h"
#include <iostream>

Faculty::Faculty() {
    facultyId = 0;
    name = "";
    department = "";
}

Faculty::Faculty(int id, std::string facultyName, std::string departmentName) {
    facultyId = id;
    name = facultyName;
    department = departmentName;
}

int Faculty::getId() const { return facultyId; }
std::string Faculty::getName() const { return name; }
std::string Faculty::getDepartment() const { return department; }

void Faculty::updateDetails(std::string facultyName, std::string departmentName) {
    name = facultyName;
    department = departmentName;
}

void Faculty::display() const {
    std::cout << "Faculty ID: " << facultyId
              << " | Name: " << name
              << " | Department: " << department << '\n';
}

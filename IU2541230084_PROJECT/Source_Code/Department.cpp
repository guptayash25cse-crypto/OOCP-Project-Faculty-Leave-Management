#include "Department.h"
#include <iostream>

Department::Department() {
    departmentId = 0;
    name = "";
}

Department::Department(int id, std::string departmentName) {
    departmentId = id;
    name = departmentName;
}

int Department::getId() const { return departmentId; }
std::string Department::getName() const { return name; }

void Department::display() const {
    std::cout << "Department ID: " << departmentId
              << " | Name: " << name << '\n';
}

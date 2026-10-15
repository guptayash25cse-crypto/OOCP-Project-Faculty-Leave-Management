#ifndef FACULTY_H
#define FACULTY_H

#include "Displayable.h"
#include <string>

class Faculty : public Displayable {
private:
    int facultyId;
    std::string name;
    std::string department;

public:
    Faculty();
    Faculty(int id, std::string facultyName, std::string departmentName);

    int getId() const;
    std::string getName() const;
    std::string getDepartment() const;
    void updateDetails(std::string facultyName, std::string departmentName);
    void display() const override;
};

#endif

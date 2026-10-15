#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Displayable.h"
#include <string>

class Department : public Displayable {
private:
    int departmentId;
    std::string name;

public:
    Department();
    Department(int id, std::string departmentName);

    int getId() const;
    std::string getName() const;
    void display() const override;
};

#endif

#ifndef DISPLAYABLE_H
#define DISPLAYABLE_H

// A small base class used to demonstrate inheritance and virtual functions.
class Displayable {
public:
    virtual void display() const = 0;
    virtual ~Displayable() { }
};

#endif

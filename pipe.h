#include <string>
#include <iostream>

class Pipe {
public:
    std::string name;
    double length;
    int diameter;
    bool under_repair;

    Pipe();

    void read();
    void display() const;
    void toggle_repair();
};

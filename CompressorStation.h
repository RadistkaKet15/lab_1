#include <string>
#include <iostream>
using namespace std;

class CompressorStation {
public:
    CompressorStation();
    // Метод для ввода данных о компрессорной станции
    void read();

    // Метод для отображения данных о компрессорной станции
    void display() const;

    // Метод для редактирования данных о компрессорной станции
    void edit();

    long num_workshops;
    string name;
    long num_workshops_in_operation;
    long efficiency;
};

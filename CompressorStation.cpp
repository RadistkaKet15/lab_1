#include "CompressorStation.h"
#include <string>
#include <iostream>
using namespace std;

const int MAX_LIMITS = 10000;

void CompressorStation::read() {
    cout << "Введите название компрессорной станции: ";
    cin >> ws;
    getline(cin, name);

    cout << "Введите количество цехов: ";
    while (!(cin >> num_workshops) || num_workshops <= 0) {
        cerr << "Ошибка: Введите корректное значение для количества цехов: ";
        cin.clear();
        cin.ignore(MAX_LIMITS, '\n');
    }

    cout << "Введите количество работающих цехов: ";
    while (!(cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
        cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
        cin.clear();
        cin.ignore(MAX_LIMITS, '\n');
    }

    cout << "Введите эффективность от 0 до 100: ";
    while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
        cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
        cin.clear();
        cin.ignore(MAX_LIMITS, '\n');
    }
}

void CompressorStation::display() const {
    cout << "Название: " << name << endl;
    cout << "Количество цехов: " << num_workshops << endl;
    cout << "Количество работающих цехов: " << num_workshops_in_operation << endl;
    cout << "Эффективность: " << efficiency << endl;
}

void CompressorStation::edit() {
    cout << "Введите новое количество работающих цехов: ";
    while (!(cin >> num_workshops_in_operation) || num_workshops_in_operation < 0 || num_workshops_in_operation > num_workshops) {
        cerr << "Ошибка: Введите корректное значение для количества работающих цехов: ";
        cin.clear();
        cin.ignore(MAX_LIMITS, '\n');
    }

    cout << "Введите новую эффективность: ";
    while (!(cin >> efficiency) || efficiency < 0 || efficiency > 100) {
        cerr << "Ошибка: Введите корректное значение эффективности от 0 до 100: ";
        cin.clear();
        cin.ignore(MAX_LIMITS, '\n');
    }
}

CompressorStation::CompressorStation() {

}

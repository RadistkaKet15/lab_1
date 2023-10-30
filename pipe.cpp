#include "pipe.h"
const int MAX_LIMITS = 10000;

Pipe::Pipe() : length(0), diameter(0), under_repair(false) {}

void Pipe::read() {
    std::cout << "Введите название трубы: ";
    std::cin >> std::ws;
    std::getline(std::cin, name);

    std::cout << "Введите длину трубы (в км): ";
    while (!(std::cin >> length) || length <= 0) {
        std::cerr << "Ошибка: Введите корректное значение для длины трубы (в км): ";
        std::cin.clear();
        std::cin.ignore(MAX_LIMITS, '\n');
    }

    std::cout << "Введите диаметр трубы: ";
    while (!(std::cin >> diameter) || diameter <= 0) {
        std::cerr << "Ошибка: Введите корректное значение для диаметра трубы: ";
        std::cin.clear();
        std::cin.ignore(MAX_LIMITS, '\n');
    }

    under_repair = false;
}

void Pipe::display() const {
    std::cout << "Название: " << name << std::endl;
    std::cout << "Длина (км): " << length << std::endl;
    std::cout << "Диаметр: " << diameter << std::endl;
    std::cout << "На ремонте: " << (under_repair ? "Да" : "Нет") << std::endl;
}

void Pipe::toggle_repair() {
    under_repair = !under_repair;
}

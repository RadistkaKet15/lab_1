#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "windows.h"
#include "pipe.h"
#include "CompressorStation.h"

using namespace std;

const int MAX_LIMITS = 10000; // Максимальное количество игнорируемых пустых строк

// Функция для сохранения данных труб в файл
void save_data_pipe(const vector<Pipe>& pipes, const string& file_name) {
    ofstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    // Сохраняем информацию о трубах
    for (const Pipe& pipe : pipes) {
        file << "Трубы\n";
        file << pipe.name << "\n";
        file << pipe.length << "\n";
        file << pipe.diameter << "\n";
        file << pipe.under_repair << "\n"; // Записываем значение bool напрямую
    }

    file.close();
}

// Функция для сохранения данных компрессорных станций в файл
void save_data_station(const vector<CompressorStation>& stations, const string& file_name) {
    ofstream file(file_name, ios::app);

    if (!file) {
        cerr << "Ошибка открытия файла для записи: " << file_name << endl;
        return;
    }

    // Сохраняем информацию о компрессорных станциях
    for (const CompressorStation& station : stations) {
        file << "Компрессорные станции\n";
        file << station.name << "\n";
        file << station.num_workshops << "\n";
        file << station.num_workshops_in_operation << "\n";
        file << station.efficiency << "\n";
    }

    file.close();
}

// Функция для загрузки данных труб из файла
void load_data_pipe(vector<Pipe>& pipes, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    // Очищаем существующие данные
    pipes.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Трубы") {
            Pipe pipe;
            file >> pipe.name >> pipe.length >> pipe.diameter >> pipe.under_repair;
            pipes.push_back(pipe);
            file.ignore(MAX_LIMITS, '\n'); // Пропускаем пустую строку
        }
    }

    file.close();
}

// Функция для загрузки данных компрессорной станции из файла
void load_data_station(vector<CompressorStation>& stations, const string& file_name) {
    ifstream file(file_name);

    if (!file) {
        cerr << "Ошибка открытия файла для чтения: " << file_name << endl;
        return;
    }

    // Очищаем существующие данные
    stations.clear();
    string line;

    while (getline(file, line)) {
        if (line == "Компрессорные станции") {
            CompressorStation station;
            file >> station.name >> station.num_workshops >> station.num_workshops_in_operation >> station.efficiency;
            stations.push_back(station);
            file.ignore(MAX_LIMITS, '\n'); // Пропускаем пустую строку
        }
    }

    file.close();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Pipe> pipes;
    vector<CompressorStation> stations;

    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить компрессорную станцию\n";
        cout << "3. Просмотреть все объекты\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать компрессорную станцию\n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "0. Выход\n";

        int choice;
        cout << "\nВведите цифру от 0 до 7, которая соответствует дальнейшему вашему действию: \n";
        while (!(cin >> choice)) {
            cerr << "Ошибка: Введите корректное значение: ";
            cin.clear();
            cin.ignore(MAX_LIMITS, '\n');
        }

        switch (choice) {
            case 0:
                exit(0); // Выход из программы
                break;
            case 1: {
                Pipe pipe;
                pipe.read();
                pipes.push_back(pipe); // Добавляем трубу в вектор
                break;
            }
            case 2: {
                CompressorStation station;
                station.read();
                stations.push_back(station); // Добавляем компрессорную станцию в вектор
                break;
            }
            case 3: {
                cout << "Трубы:\n";
                for (const Pipe& pipe : pipes) {
                    pipe.display();
                    cout << endl;
                }
                cout << "Компрессорные станции:\n";
                for (const CompressorStation& station : stations) {
                    station.display();
                    cout << endl;
                }
                break;
            }
            case 4: {
                string pipe_name;
                cout << "Введите название трубы для редактирования: ";
                cin >> pipe_name;
                bool found = false;
                for (Pipe& pipe : pipes) {
                    if (pipe.name == pipe_name) {
                        pipe.toggle_repair();
                        cout << "Состояние трубы '" << pipe.name << "' изменено 'На ремонте: " << (pipe.under_repair ? "Да" : "Нет") << "'\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cerr << "Труба с указанным названием не найдена. Попробуйте еще раз или создайте трубу с этим названием.\n";
                }
                break;
            }
            case 5: {
                string station_name;
                cout << "Введите название компрессорной станции для редактирования: ";
                cin >> station_name;
                bool found = false;
                for (CompressorStation& station : stations) {
                    if (station.name == station_name) {
                        station.edit();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cerr << "Компрессорная станция с указанным названием не найдена. Попробуйте еще раз или создайте станцию с этим названием.\n";
                }
                break;
            }
            case 6: {
                string file_name;
                cout << "Введите имя файла для сохранения ('имя файла.txt'): ";
                cin >> file_name;
                save_data_pipe(pipes, file_name);
                save_data_station(stations, file_name);
                cout << "Данные сохранены в файл: " << file_name << endl;
                break;
            }
            case 7: {
                string load_file_name;
                cout << "Введите имя файла для загрузки ('имя файла.txt'): ";
                cin >> load_file_name;
                load_data_pipe(pipes, load_file_name);
                load_data_station(stations, load_file_name);
                cout << "Данные загружены из файла: " << load_file_name << endl;
                break;
            }
            default: {
                cerr << "Неверный выбор. Попробуйте снова.\n";
                break;
            }
        }
    }

    return 0;
}

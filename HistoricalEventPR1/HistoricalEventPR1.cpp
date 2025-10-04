#include <iostream>   
#include <fstream>  
#include <vector>     
#include <string>     
using namespace std;

// Структура "Историческое событие"
struct Event {
    string type;
    string name;   
    string date;   
    string extra;
};

void printEvent(const Event& e) {
    if (e.type == "BATTLE") {
        cout << "Битва: " << e.name
            << ", дата: " << e.date
            << ", место: " << e.extra << endl;
    }
    else if (e.type == "TREATY") {
        cout << "Договор: " << e.name
            << ", дата: " << e.date
            << ", стороны: " << e.extra << endl;
    }
}

void removeEvent(vector<Event>& events, const string& arg) {
    bool isYear = true;
    for (char c : arg) {
        if (!isdigit(c)) {
            isYear = false;
            break;
        }
    }

    if (isYear) {
        for (size_t i = events.size(); i-- > 0;) {
            if (events[i].date > arg) {
                events.erase(events.begin() + i);
            }
        }
    }
    else {
        for (size_t i = events.size(); i-- > 0;) {
            if (events[i].name == arg) {
                events.erase(events.begin() + i);
            }
        }
    }
}


int main() {
    setlocale(0, "");
    vector<Event> events;
    ifstream file("commands.txt");
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл commands.txt" << endl;
        return 1;
    }

    string cmd;

    // Читаем команды из файла
    while (file >> cmd) {
        if (cmd == "ADD") {
            Event e;
            file >> e.type >> e.name >> e.date >> e.extra;
            events.push_back(e); // добавляем структуру в конец вектора
        }
        else if (cmd == "PRINT") {
            for (const Event& e : events) {
                printEvent(e);
            }
            cout << "---------------------------------------------------------------" << endl;
        }
        else if (cmd == "REM") {
            string arg;
            file >> arg;
            removeEvent(events, arg);  
        }
    }
    return 0;
}

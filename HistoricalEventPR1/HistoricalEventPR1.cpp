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

int main() {
    setlocale(0, "");
    vector<Event> events;     
    ifstream file("commands.txt");
    string cmd;                // Для чтения команд (ADD, REM, PRINT)

    // Читаем команды из файла
    while (file >> cmd) {
        if (cmd == "ADD") {
            Event e;
            file >> e.type >> e.name >> e.date >> e.extra;
            events.push_back(e); // добавляем структуру в конец вектора
        }
        else if (cmd == "PRINT") {
            for (auto& e : events) { // перебирает все объекты в контейнере
                if (e.type == "BATTLE") {
                    cout << "Битва: " << e.name<< ", дата: " << e.date<< ", место: " << e.extra << endl;
                }
                else if (e.type == "TREATY") {
                    cout << "Договор: " << e.name << ", дата: " << e.date<< ", стороны: " << e.extra << endl;
                }
            }
            cout << "---------------------------------------------------------------/" << endl;
        }
        else if (cmd == "REM") {
            string arg;
            file >> arg;


            bool isYear = true;
            for (char c : arg) {
                if (!isdigit(c)) {
                    isYear = false;
                    break;
                }
            }

            for (size_t i = events.size(); i-- > 0;) {
                if (isYear) {
                    if (events[i].date > arg) {
                        events.erase(events.begin() + i);
                    }
                }
                else {
                    if (events[i].name == arg) {
                        events.erase(events.begin() + i);
                    }
                }
            }
        }

    }
    return 0;
}

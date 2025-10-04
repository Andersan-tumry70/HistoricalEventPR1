#include "HistoricalEvent.h"
#include <iostream>
#include <cctype>

using namespace std;

void printEvent(const Event& e) {
    if (e.type == "BATTLE") {
        cout << "Battle: " << e.name
            << ", date: " << e.date
            << ", place: " << e.extra << endl;
    }
    else if (e.type == "TREATY") {
        cout << "Treaty: " << e.name
            << ", date: " << e.date
            << ", sides: " << e.extra << endl;
    }
}


void removeEvent(vector<Event>& events, const std::string& arg) {
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

#pragma once
#include <string>
#include <vector>

struct Event {
    std::string type;
    std::string name;
    std::string date;
    std::string extra;
};

void printEvent(const Event& e);
void removeEvent(std::vector<Event>& events, const std::string& arg);

#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include "../HistoricalEventPR1/HistoricalEvent.h"

using namespace std;

// ���� ���������� �������
TEST(EventTest, AddEvent) {
    vector<Event> events;

    Event e1 = { "BATTLE", "Great Battle", "2025", "Battlefield" };
    events.push_back(e1);

    // ���������, ��� ������� ���������
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].name, "Great Battle");
    ASSERT_EQ(events[0].type, "BATTLE");

    Event e2 = { "TREATY", "Peace Treaty", "2023", "Sides" };
    events.push_back(e2);

    // ��������� ������ �������
    ASSERT_EQ(events.size(), 2);
    ASSERT_EQ(events[1].type, "TREATY");
    ASSERT_EQ(events[1].extra, "Sides");
}

// ���� �������� �������
TEST(EventTest, RemoveEvent) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle 1", "2024", "Place" });
    events.push_back({ "TREATY", "Treaty 1", "2023", "Sides" });

    // ������� ������� � date > "2023"
    removeEvent(events, "2023");
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].name, "Treaty 1"); // ��������� ���������� �������

    // ������� �� �����
    removeEvent(events, "Treaty 1");
    ASSERT_TRUE(events.empty()); // ���������, ��� ������ ����
}

// ���� ������ ������� (�������� cout)
TEST(EventTest, PrintEvent) {
    Event e1 = { "BATTLE", "Battle Test", "2022", "Field" };
    Event e2 = { "TREATY", "Treaty Test", "2021", "Sides" };

    ostringstream out;
    streambuf* coutBuf = cout.rdbuf();   // ��������� ������� ����� cout
    cout.rdbuf(out.rdbuf());             // �������������� cout � ostringstream

    printEvent(e1);
    printEvent(e2);

    cout.rdbuf(coutBuf);                 // ��������������� cout

    string output = out.str();
    // ���������, ��� ����� �������� ������ �������
    ASSERT_NE(output.find("Battle: Battle Test"), string::npos);
    ASSERT_NE(output.find("Treaty: Treaty Test"), string::npos);
}

// ���� �������� �������������� �������
TEST(EventTest, InvalidRemove) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle", "2025", "Place" });

    removeEvent(events, "Nonexistent");  // ������� �������������� �������
    ASSERT_EQ(events.size(), 1);         // ���������, ��� ������� ��������

    removeEvent(events, "2030");         // ������� ������� � date > "2030"
    ASSERT_EQ(events.size(), 1);         // ������ �� ���������
}

// ���� �������� �� ������� �������
TEST(EventTest, RemoveFromEmptyVector) {
    vector<Event> events;
    removeEvent(events, "2025");         // �������� ������� �� ������� �������
    ASSERT_TRUE(events.empty());
}

// ���� ������������� ����
TEST(EventTest, RemoveInvalidYear) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle", "2025", "Place" });

    removeEvent(events, "20X5");         
    ASSERT_EQ(events.size(), 1);         // ������� ������ ��������
}

TEST(EventTest, PreventEmptyName) {
    vector<Event> events;

    Event e1 = { "BATTLE", "", "2025", "Field" };

    if (!e1.name.empty()) {
        events.push_back(e1);
    }

    ASSERT_TRUE(events.empty());
}

TEST(EventTest, DateMustBeNumber) {
    vector<Event> events;

    auto addEvent = [&](const Event& e) {
        if (e.date.size() != 4 || !all_of(e.date.begin(), e.date.end(), ::isdigit)) {
            throw invalid_argument("Invalid date");
        }
        events.push_back(e);
        };

    Event e1 = { "BATTLE", "Battle", "20/25", "Field" };
    Event e2 = { "TREATY", "Treaty", "2025", "Sides" }; 

    ASSERT_THROW(addEvent(e1), invalid_argument);

}
// main ��� ������� ���� ������
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

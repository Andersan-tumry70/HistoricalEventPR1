#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include "../HistoricalEventPR1/HistoricalEvent.h"

using namespace std;

// “ест добавлени€ событий
TEST(EventTest, AddEvent) {
    vector<Event> events;

    Event e1 = { "BATTLE", "Great Battle", "2025", "Battlefield" };
    events.push_back(e1);

    // ѕровер€ем, что событие добавлено
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].name, "Great Battle");
    ASSERT_EQ(events[0].type, "BATTLE");

    Event e2 = { "TREATY", "Peace Treaty", "2023", "Sides" };
    events.push_back(e2);

    // ѕровер€ем второе событие
    ASSERT_EQ(events.size(), 2);
    ASSERT_EQ(events[1].type, "TREATY");
    ASSERT_EQ(events[1].extra, "Sides");
}

// “ест удалени€ событий
TEST(EventTest, RemoveEvent) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle 1", "2024", "Place" });
    events.push_back({ "TREATY", "Treaty 1", "2023", "Sides" });

    // ”дал€ем событи€ с date > "2023"
    removeEvent(events, "2023");
    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0].name, "Treaty 1"); // провер€ем оставшеес€ событие

    // ”дал€ем по имени
    removeEvent(events, "Treaty 1");
    ASSERT_TRUE(events.empty()); // провер€ем, что вектор пуст
}

// “ест печати событий (перехват cout)
TEST(EventTest, PrintEvent) {
    Event e1 = { "BATTLE", "Battle Test", "2022", "Field" };
    Event e2 = { "TREATY", "Treaty Test", "2021", "Sides" };

    ostringstream out;
    streambuf* coutBuf = cout.rdbuf();   // сохран€ем текущий поток cout
    cout.rdbuf(out.rdbuf());             // перенаправл€ем cout в ostringstream

    printEvent(e1);
    printEvent(e2);

    cout.rdbuf(coutBuf);                 // восстанавливаем cout

    string output = out.str();
    // ѕровер€ем, что вывод содержит строки событий
    ASSERT_NE(output.find("Battle: Battle Test"), string::npos);
    ASSERT_NE(output.find("Treaty: Treaty Test"), string::npos);
}

// “ест удалени€ несуществующих событий
TEST(EventTest, InvalidRemove) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle", "2025", "Place" });

    removeEvent(events, "Nonexistent");  // удал€ем несуществующее событие
    ASSERT_EQ(events.size(), 1);         // провер€ем, что событие осталось

    removeEvent(events, "2030");         // удал€ем событи€ с date > "2030"
    ASSERT_EQ(events.size(), 1);         // ничего не удалилось
}

// “ест удалени€ из пустого вектора
TEST(EventTest, RemoveFromEmptyVector) {
    vector<Event> events;
    removeEvent(events, "2025");         // пытаемс€ удалить из пустого вектора
    ASSERT_TRUE(events.empty());
}

// “ест некорректного года
TEST(EventTest, RemoveInvalidYear) {
    vector<Event> events;
    events.push_back({ "BATTLE", "Battle", "2025", "Place" });

    removeEvent(events, "20X5");         // некорректный год
    ASSERT_EQ(events.size(), 1);         // событие должно остатьс€
}

// main дл€ запуска всех тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

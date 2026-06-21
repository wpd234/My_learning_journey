#ifndef TIME_H
#define TIME_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Time {
private:
    int year;
    int month;
    int day;
    bool isValidDate(int y, int m, int d) const;
    bool isLeapYear(int y) const;
    int getDaysInMonth(int y, int m) const;
public:
    Time(int y, int m, int d);
    Time(const string& dateStr);
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;
    bool operator<(const Time& other) const;
    bool operator<=(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator>=(const Time& other) const;
    int operator-(const Time& other) const;
    string toString() const;
    bool parseFromString(const string& dateStr);
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    string getMonthName() const;
    bool isSameDay(const Time& other) const;
    int getDaysInMonth() const;
    int getWeekDay() const;
    Time addDays(int days) const;
};

#endif
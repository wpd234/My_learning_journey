#include "Time.h"
#include <iostream>
#include <ctime>

using namespace std;

bool Time::isLeapYear(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Time::getDaysInMonth(int y, int m) const {
    static const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if (m == 2 && isLeapYear(y)) {
        return 29;
    }

    if (m >= 1 && m <= 12) {
        return daysInMonth[m - 1];
    }

    return 0;
}

bool Time::isValidDate(int y, int m, int d) const {
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > getDaysInMonth(y, m)) return false;
    return true;
}

Time::Time(int y, int m, int d) {
    if (!isValidDate(y, m, d)) {
        cout << "错误：无效的日期 " << y << "-" << m << "-" << d << endl;
        year = 2026;
        month = 1;
        day = 1;
        return;
    }

    year = y;
    month = m;
    day = d;
}

Time::Time(const string& dateStr) {
    if (!parseFromString(dateStr)) {
        cout << "错误：无法解析日期 " << dateStr << endl;
        year = 2026;
        month = 1;
        day = 1;
    }
}

bool Time::operator==(const Time& other) const {
    return (year == other.year && month == other.month && day == other.day);
}

bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

bool Time::operator<(const Time& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Time::operator<=(const Time& other) const {
    return (*this < other) || (*this == other);
}

bool Time::operator>(const Time& other) const {
    return !(*this <= other);
}

bool Time::operator>=(const Time& other) const {
    return !(*this < other);
}

int Time::operator-(const Time& other) const {
    int days = 0;
    Time start = other;
    Time end = *this;
    if (start > end) {
        swap(start, end);
    }
    while (start < end) {
        days++;
        start = start.addDays(1);
    }

    return days;
}

string Time::toString() const {
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d",
        year, month, day);//格式化输入字符缓冲区
    return string(buffer);
}

bool Time::parseFromString(const string& dateStr) {
    int y, m, d;
    char sep1, sep2;

    stringstream ss(dateStr);
    if (ss >> y >> sep1 >> m >> sep2 >> d) {//字符串流，根据int、char、int、char、int的格式解析日期字符串
        if ((sep1 == '-' || sep1 == '/') && (sep2 == '-' || sep2 == '/')) {
            if (isValidDate(y, m, d)) {
                year = y;
                month = m;
                day = d;
                return true;
            }
        }
    }
    return false;
}//将字符串日期格式解析为Time对象

void Time::setYear(int y) {
    if (isValidDate(y, month, day)) {
        year = y;
    }
    else {
		cout << "错误：年份无效" << endl;
    }
}

void Time::setMonth(int m) {
    if (isValidDate(year, m, day)) {
        month = m;
    }
    else {
        cerr << "错误：月份无效" << endl;
    }
}

void Time::setDay(int d) {
    if (isValidDate(year, month, d)) {
        day = d;
    }
    else {
        cerr << "错误：日期无效" << endl;
    }
}

string Time::getMonthName() const {
    static const string months[] = {"一月", "二月", "三月", "四月", "五月", "六月",
								   "七月", "八月", "九月", "十月", "十一月", "十二月" };
    return months[month - 1];
}

bool Time::isSameDay(const Time& other) const {
    return (year == other.year && month == other.month && day == other.day);
}

int Time::getDaysInMonth() const {
    return getDaysInMonth(year, month);
}

int Time::getWeekDay() const {
    // 基姆拉尔森计算公式，返回1-7（周一到周日）
    int y = year;
    int m = month;
    int d = day;
    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }
    int weekDay = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
    if (weekDay == 0) weekDay = 7;
    return weekDay;
}

Time Time::addDays(int days) const {
    Time result = *this;

    while (days > 0) {
        result.day++;
        if (result.day > getDaysInMonth(result.year, result.month)) {
            result.day = 1;
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
        days--;
    }

    while (days < 0) {
        result.day--;
        if (result.day < 1) {
            result.month--;
            if (result.month < 1) {
                result.month = 12;
                result.year--;
            }
            result.day = getDaysInMonth(result.year, result.month);
        }
        days++;
    }

    return result;
}
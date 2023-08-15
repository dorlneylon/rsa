#include "Date.h"
#include <chrono>

Date::Date() {
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm* time_info = std::localtime(&current_time);

    year = time_info->tm_year + 1900;
    month = time_info->tm_mon + 1;
    day = time_info->tm_mday;
    hour = time_info->tm_hour;
    min = time_info->tm_min;
    sec = time_info->tm_sec;
}

Date::Date(int8_t sec, int8_t min, int8_t hrs, int8_t dd, int8_t mm, int32_t yy):
        sec(sec), min(min), hour(hrs), day(dd), month(mm), year(yy) {}

void Date::setSec(int8_t sec) {
    this->sec = sec;
}

void Date::setMin(int8_t min) {
    this->min = min;
}

void Date::setHour(int8_t hour) {
    this->hour = hour;
}

void Date::setDay(int8_t day) {
    this->day = day;
}

void Date::setMonth(int8_t month) {
    this->month = month;
}

void Date::setYear(int32_t year) {
    this->year = year;
}

void Date::add(const Date* other) {
    adjustTime(other->sec, other->min, other->hour, other->day, other->month, other->year);
}

void Date::sub(const Date* other) {
    adjustTime(-other->sec, -other->min, -other->hour, -other->day, -other->month, -other->year);
}

void Date::adjustTime(std::int8_t s, std::int8_t m, std::int8_t h, std::int8_t d,
                std::int8_t mon, std::int32_t y) {
    sec += s; min += m; hour += h; day += d; month += mon; year += y;
    min += sec / 60; sec %= 60; hour += min / 60; min %= 60; day += hour / 24; hour %= 24;
    month += (day - 1) / daysInMonth(year, month); day = (day - 1) % daysInMonth(year, month) + 1;
    year += month / 12; month = (month % 12 + 12) % 12;
}

int8_t Date::daysInMonth(int32_t year, int8_t month) {
    if (month == 2)
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return 29;
        else
            return 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

bool Date::compare(const Date* date) {
    return date == this;
}

bool Date::operator==(const Date& rhs) {
    return
            std::tie(year, month, day, hour, min, sec) ==
                        std::tie(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.min, rhs.sec);
}

bool Date::operator<=(const Date& rhs) {
    return
            std::tie(year, month, day, hour, min, sec) <=
                        std::tie(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.min, rhs.sec);
}

int8_t Date::getSec() {
    return sec;
}

int8_t Date::getMin() {
    return min;
}

int8_t Date::getHour() {
    return hour;
}

int8_t Date::getDay() {
    return day;
}

int8_t Date::getMonth() {
    return month;
}

int32_t Date::getYear() {
    return year;
}

Date::~Date() = default;
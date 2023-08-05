#include "Date.h"

Date::Date(): day(0), month(0), year(0), hour(0), min(0), sec(0) {}

Date::Date(std::int8_t sec, std::int8_t min, std::int8_t hrs, std::int8_t dd, std::int8_t mm, std::int32_t yy):
        sec(sec), min(min), hour(hrs), day(dd), month(mm), year(yy) {}

void Date::setSec(std::int8_t sec) {
    this->sec = sec;
}

void Date::setMin(std::int8_t min) {
    this->min = min;
}

void Date::setHour(std::int8_t hour) {
    this->hour = hour;
}

void Date::setDay(std::int8_t day) {
    this->day = day;
}

void Date::setMonth(std::int8_t month) {
    this->month = month;
}

void Date::setYear(std::int32_t year) {
    this->year = year;
}

void Date::adjustTime(std::int32_t target, std::int32_t carry, std::int32_t limit) {
    target += carry;
    carry = target / limit;
    target %= limit;
}

void Date::add(const Date* date) {
    adjustTime(sec, date->sec, 60);
    adjustTime(min, date->min, 60);
    adjustTime(hour, date->hour, 24);
    adjustTime(day, date->day, 30);
    adjustTime(month, date->month, 12);
    year += date->year;
}

void Date::sub(const Date* date) {
    adjustTime(sec, -date->sec, 60);
    adjustTime(min, -date->min, 60);
    adjustTime(hour, -date->hour, 24);
    adjustTime(day, -date->day, 30);
    adjustTime(month, -date->month, 12);
    year -= date->year;
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
//
// Created by nylon on 31.07.2023.
//

#ifndef DATE_H
#define DATE_H
#include <cstdint>
#include <tuple>


class Date {
public:
    Date();
    Date(std::int8_t, std::int8_t, std::int8_t, std::int8_t, std::int8_t, std::int32_t);
    void setSec(std::int8_t);
    void setMin(std::int8_t);
    void setHour(std::int8_t);
    void setDay(std::int8_t);
    void setMonth(std::int8_t);
    void setYear(std::int32_t);
    void add(const Date*);
    void sub(const Date*);
    bool compare(const Date*);
    bool operator==(const Date&);
    bool operator<=(const Date&);
    std::int8_t getSec();
    std::int8_t getMin();
    std::int8_t getHour();
    std::int8_t getDay();
    std::int8_t getMonth();
    std::int32_t getYear();
    ~Date();
private:
    void adjustTime(std::int32_t, std::int32_t, std::int32_t);
    std::int8_t sec, min, hour, day, month;
    std::int32_t year;
};


#endif //DATE_H

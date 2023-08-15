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
    Date(int8_t, int8_t, int8_t, int8_t, int8_t, int32_t);
    void setSec(int8_t);
    void setMin(int8_t);
    void setHour(int8_t);
    void setDay(int8_t);
    void setMonth(int8_t);
    void setYear(int32_t);
    void add(const Date*);
    void sub(const Date*);
    bool compare(const Date*);
    bool operator==(const Date&);
    bool operator<=(const Date&);
    int8_t getSec();
    int8_t getMin();
    int8_t getHour();
    int8_t getDay();
    int8_t getMonth();
    int32_t getYear();
    ~Date();
private:
    std::int8_t sec, min, hour, day, month;
    std::int32_t year;

    void adjustTime(int8_t, int8_t, int8_t, int8_t,
                    int8_t, int32_t);

    int8_t daysInMonth(int32_t, int8_t);
};


#endif //DATE_H

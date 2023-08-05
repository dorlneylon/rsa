//
// Created by nylon on 31.07.2023.
//

#ifndef BIGINT_H
#define BIGINT_H
#include <cstdint>
#include <cstring>
#include <cmath>
#include <complex>
#include <iostream>
#include "ftype.h"

const double pi = acos(-1);
const std::int32_t maxn = 1<<20;
const std::int32_t logn = 20;

class BigInt {
public:
    BigInt();
    BigInt(const char*);
    BigInt(const int64_t n);
    BigInt(const BigInt&);
    ~BigInt();

    // Binary arithmetic operators:
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator%(const BigInt&) const;

    // Arithmetic-assignment operators:
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    BigInt operator+() const;   // unary +
    BigInt operator-() const;   // unary -

    // Relational operators:
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;

    BigInt& operator=(const BigInt&);

    // Handlers
    void set(const char*);
    void set(const BigInt& n);
    bool getSign() const;
    std::int32_t getLength() const;
    std::int32_t* getNumber() const;
    void print();
private:
    void resize(std::int32_t);
    void setSign(bool);
    void mul(const BigInt&, const BigInt&, BigInt&) const;
    void div(const BigInt&, const BigInt&, BigInt&, BigInt&);
    std::int32_t* number;
    bool pos;
    std::int32_t length;
};

#endif //BIGINT_H

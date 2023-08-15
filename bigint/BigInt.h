//
// Created by nylon on 31.07.2023.
//

#ifndef BIGINT_H
#define BIGINT_H
#include <cstdint>
#include <cstring>
#include <cmath>
#include <iostream>
#include <set>
#include "../structures/ftype.h"
#include "../structures/array.h"

const long double pi = acosl(-1.0);
const uint64_t base = 1e6;

class BigInt {
public:
    BigInt();
    BigInt(const char*);
    BigInt(const int64_t);
    BigInt(const BigInt&);
    ~BigInt();

    // Binary arithmetic operators:
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator*(const uint64_t&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator/(const uint64_t&) const;
    BigInt operator%(const BigInt&) const;
    uint64_t operator%(const uint64_t&);

    // Arithmetic-assignment operators:
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const uint64_t&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator/=(const uint64_t&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator%=(const uint64_t&);

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
    uint32_t getLength() const;
    const array<uint64_t>& getNumber() const;
    void print();
    void print(std::ostream&) const;
private:
    void resize(uint32_t);
    void setSign(bool);
    bool abs_compare(const BigInt&, const BigInt&) const;
    void mul(const BigInt &, const BigInt&, BigInt&) const;
    void mul(const BigInt&, const uint64_t&, BigInt&) const;
    void div(const BigInt&, const BigInt&, BigInt&, BigInt&);
    void div(const BigInt&, const uint64_t&, BigInt&, uint64_t&);
    array<uint64_t> number;
    bool pos;
};

#endif //BIGINT_H

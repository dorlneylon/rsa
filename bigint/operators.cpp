//
// Created by nylon on 03.08.2023.
//

#include "BigInt.h"

BigInt BigInt::operator+() const {
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt res;
    res.set(*this);
    res.setSign(!pos);
    return res;
}

BigInt& BigInt::operator=(const BigInt& a) {
    this->set(a);
    return *this;
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt res;
    res.set(*this);
    res += other;
    return res;
}

BigInt BigInt::operator-(const BigInt &other) const {
    BigInt res;
    res.set(*this);
    res -= other;
    return res;
}

BigInt& BigInt::operator+=(const BigInt& a) {
    if (this->getSign() != a.getSign())
            return this->getSign() ?
                       abs_compare(*this,a) ? *this -= -a : *this = -(-a - *this) :
                          abs_compare(*this,a) ? *this = -(-*this - a) : *this = a - -*this;
    bool sgn = *this >= -a;
    uint64_t carry = 0;
    for (uint32_t i = 0; i < std::max(getLength(), a.getLength()) || carry; ++i) {
        if (i == getLength())
            number.pb(0);
        number[i] += carry + (i < a.getLength() ? a.number[i] : 0);
        carry = number[i] >= base;
        if (carry) number[i] -= base;
    }
    this->setSign(sgn);
    return *this;
}

bool BigInt::abs_compare(const BigInt& a, const BigInt& b) const {
    if (a.getLength() != b.getLength()) return a.getLength() > b.getLength();
    for (int32_t i = a.getLength() - 1; i >= 0; --i)
        if (a.getNumber()[i] != b.getNumber()[i]) return a.getNumber()[i] > b.getNumber()[i];
    return true;
}

BigInt& BigInt::operator-=(const BigInt& a) {
    if (this->getSign() != a.getSign())
        return this->getSign() ?
               abs_compare(*this,a) ? *this += -a : *this = -(-a + *this) :
                    abs_compare(*this,a) ? *this = -(-*this + a) : *this = -a - -*this;
    bool sgn = *this >= a;
    if (!abs_compare(*this,a)) return *this = -(a - *this);
    uint64_t carry = 0;
    for (uint32_t i = 0; i < a.getLength() || carry; ++i) {
        number[i] -= carry + (i < a.getLength() ? a.number[i] : 0);
        carry = number[i] >= base;
        if (carry) number[i] += base;
    }
    while (number.getSize() > 1 && number[getLength()-1] == 0)
        number.pop();
    this->setSign(sgn);
    return *this;
}

BigInt BigInt::operator*(const BigInt &a) const {
    BigInt res;
    res.pos = pos == a.pos;
    mul(*this, a, res);
    return res;
}

BigInt& BigInt::operator*=(const BigInt& other) {
    BigInt res;
    res.pos = pos == other.pos;
    mul(*this, other, res);
    this->set(res);
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& other) {
    BigInt quo, rem;
    bool p = this->getSign() == other.getSign();
    this->setSign(true);
    if (other.getSign()) div(*this, other, quo, rem);
    else div(*this, -other, quo, rem);
    this->set(quo);
    this->setSign(p);
    return *this;
}

BigInt BigInt::operator*(const uint64_t& a) const {
    BigInt res;
    res.set(*this);
    res *= a;
    return res;
}

BigInt& BigInt::operator%=(const BigInt& other) {
    assert(other > BigInt("0") && "Modulo only by positive");
    BigInt quo, rem;
    bool p = this->pos;
    this->pos = true;
    div(*this, other, quo, rem);
    if (p) this->set(rem);
    else this->set(other-rem);
    return *this;
}

BigInt& BigInt::operator%=(const uint64_t& n) {
    assert(n > 0 && "Modulo by positive and less than 10^6");
    BigInt quo;
    uint64_t rem;
    bool p = this->pos;
    this->pos = true;
    div(*this, n, quo, rem);
    if (p) this->set(std::to_string(rem).c_str());
    else this->set(std::to_string(n-rem).c_str());
    return *this;
}

BigInt& BigInt::operator/=(const uint64_t& n) {
    assert(n < base && "Divisor must be less than 10^6. Use BigInt instead.");
    BigInt quo;
    uint64_t rem;
    bool p = this->getSign();
    this->setSign(true);
    div(*this, n, quo, rem);
    this->set(quo);
    this->setSign(p);
    return *this;
}

bool BigInt::operator<(const BigInt& other) const {
    if (pos != other.pos)
        return pos < other.pos;

    if (getLength() != other.getLength())
        return (getLength() < other.getLength()) ^ !pos;

    for (int32_t i = getLength() - 1; i >= 0; --i) {
        if (number[i] != other.number[i])
            return (number[i] < other.number[i]) ^ !pos;
    }

    return false;
}

BigInt BigInt::operator/(const BigInt& other) const {
    BigInt res = *this;
    res /= other;
    return res;
}

BigInt BigInt::operator/(const uint64_t& n) const {
    BigInt res = *this;
    res /= n;
    return res;
}

BigInt BigInt::operator%(const BigInt& other) const {
    BigInt res = *this;
    res %= other;
    return res;
}

uint64_t BigInt::operator%(const uint64_t& n) {
    uint64_t rem;
    BigInt quo;
    div(*this, n, quo, rem);
    return rem;
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(other < *this);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

bool BigInt::operator==(const BigInt& other) const {
    if (pos != other.pos || getLength() != other.getLength()) return false;
    for (int32_t i = getLength() - 1; i >= 0; --i) {
        if (number[i] != other.number[i]) return false;
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

BigInt& BigInt::operator*=(const uint64_t &n) {
    assert(n <= base && "Multiplier must be less than 10^6. Use BigInt instead.");
    BigInt res;
    mul(*this, n, res);
    this->set(res);
    return *this;
}

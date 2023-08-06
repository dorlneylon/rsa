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

// да простят меня за этот кошмар. у меня кончились силы в попытках сделать это нормально, и я захардкодил -= и +=.
BigInt& BigInt::operator+=(const BigInt& other) {
    if (pos != other.pos) {
        BigInt tmp1, tmp2;
        tmp1.set(*this), tmp2.set(other);
        if (pos) {
            tmp2.setSign(true);
            tmp1 -= tmp2;
            this->set(tmp1);
            this->setSign(pos);
            return *this;
        }
        else {
            tmp1.setSign(true);
            tmp2 -= tmp1;
            this->set(tmp2);
            this->setSign(tmp1 < tmp2);
            return *this;
        }
    } else {
        if (pos) {
            uint32_t maxLength = std::max(getLength(), other.getLength());

            BigInt result;
            result.resize(maxLength + 1);

            uint64_t carry = 0;
            for (uint32_t i = 0; i < maxLength; ++i) {
                uint64_t sum = carry;
                if (i < getLength()) sum += number[i];
                if (i < other.getLength()) sum += other.number[i];
                result.number[i] = sum % base;
                carry = sum / base;
            }

            if (carry > 0) {
                result.number[maxLength] = carry;
                result.number.resize(maxLength + 1);
            } else
                result.number.resize(maxLength);

            this->set(result);
            return *this;
        } else {
            BigInt tmp1, tmp2;
            tmp1.set(*this);
            tmp1.setSign(true);
            tmp2.set(other);
            tmp2.setSign(true);
            tmp1 += tmp2;
            this->set(tmp1);
            this->setSign(false);
            return *this;
        }
    }
}


BigInt& BigInt::operator-=(const BigInt& other) {
    if (pos != other.pos) {
        if (pos) {
            BigInt tmp;
            tmp.set(other);
            tmp.setSign(true);
            *this += tmp;
            return *this;
        } else {
            BigInt tmp;
            tmp.set(*this);
            tmp.setSign(true);
            this->set(other);
            *this += tmp;
            this->setSign(false);
            return *this;
        }
    } else {
        if (pos && *this >= other) {
            int64_t borrow = 0;
            for (uint32_t i = 0; i < getLength(); ++i) {
                int64_t sub = number[i] - (i < other.getLength() ? other.number[i] : 0) - borrow;
                if (sub < 0) {
                    sub += base;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                number[i] = sub;
            }
            while (getLength() > 1 && number[getLength() - 1] == 0) number.pop();
        } else if (pos && *this < other) {
            BigInt tmp;
            tmp.set(other);
            tmp -= *this;
            this->set(tmp);
            pos = !other.pos;
        } else if (!pos && *this < other) {
            BigInt tmp1, tmp2;
            tmp1.set(other);
            tmp1.setSign(true);
            tmp2.set(*this);
            tmp2.setSign(true);
            tmp1 -= tmp2;
            this->set(tmp1);
            pos = false;
        } else if (!pos && *this >= other) {
            BigInt tmp1, tmp2;
            tmp1.set(other);
            tmp1.setSign(true);
            tmp2.set(*this);
            tmp2.setSign(true);
            tmp2 -= tmp1;
            this->set(tmp2);
            pos = true;
        }
    }
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

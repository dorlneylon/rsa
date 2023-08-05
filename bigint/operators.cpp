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
        if (pos) {
            BigInt tmp1, tmp2;
            tmp1.set(*this);
            tmp2.set(other);
            tmp2.setSign(true);
            tmp1 -= tmp2;
            this->set(tmp1);
            this->setSign(pos);
            return *this;
        }
        else {
            BigInt tmp1, tmp2;
            tmp1.set(*this);
            tmp1.setSign(true);
            tmp2.set(other);
            tmp2 -= tmp1;
            this->set(tmp2);
            this->setSign(tmp1 < tmp2);
            return *this;
        }
    } else {
        if (pos) {
            int32_t maxLength = std::max(length, other.length);

            BigInt result;
            result.resize(maxLength + 1);

            int32_t carry = 0;
            for (int32_t i = 0; i < maxLength; ++i) {
                int32_t sum = carry;
                if (i < length) sum += number[i];
                if (i < other.length) sum += other.number[i];
                result.number[i] = sum % 10;
                carry = sum / 10;
            }

            if (carry > 0) {
                result.number[maxLength] = carry;
                result.length = maxLength + 1;
            } else
                result.length = maxLength;

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
            int32_t borrow = 0;
            for (int32_t i = 0; i < length; ++i) {
                int32_t sub = number[i] - (i < other.length ? other.number[i] : 0) - borrow;
                if (sub < 0) {
                    sub += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                number[i] = sub;
            }
            while (length > 1 && number[length - 1] == 0) {
                --length;
            }
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
    this->set(*this * other);
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

bool BigInt::operator<(const BigInt& other) const {
    if (pos != other.pos)
        return pos < other.pos;

    if (length != other.length)
        return (length < other.length) ^ !pos;

    for (int i = length - 1; i >= 0; --i) {
        if (number[i] != other.number[i])
            return (number[i] < other.number[i]) ^ !pos;
    }

    return false;
}

BigInt BigInt::operator/(const BigInt& other) const {
    BigInt res;
    res.set(*this);
    res /= other;
    return res;
}
BigInt BigInt::operator%(const BigInt& other) const {
    BigInt res;
    res.set(*this);
    res %= other;
    return res;
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
    return pos == other.pos && length == other.length && std::equal(number, number + length, other.number);
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}
//
// Created by nylon on 31.07.2023.
//

#include <iomanip>
#include "BigInt.h"

BigInt::BigInt(): number(array<uint64_t>()), pos(true) {}

BigInt::BigInt(const int64_t n) {
    pos = n >= 0;
    set(std::to_string(std::abs(n)).c_str());
}

namespace fft {
    array<uint32_t> rev;
    array<ftype> wn;

    void fft(array<ftype> &a, uint32_t n) {
        for (std::uint32_t i = 0; i < n; ++i)
            if (i < rev[i])
                std::swap(a[i], a[rev[i]]);
        for (std::uint32_t len = 2; len <= n; len <<= 1) {
            long double ang = 2 * pi / len;
            std::uint32_t len2 = len >> 1;
            ftype w(cosl(ang), sinl(ang));
            wn[0] = ftype(1, 0);
            for (std::uint32_t i = 1; i < len2; ++i)
                wn[i] = wn[i - 1] * w;
            for (std::uint32_t i = 0; i < n; i += len) {
                ftype t;
                for (std::uint32_t j = 0; j < len2; ++j) {
                    t = wn[j] * a[i + j + len2];
                    ftype u = a[i + j];
                    a[i + j] = u + t;
                    a[i + j + len2] = u - t;
                }
            }
        }
    }

    void calcRev(uint32_t n) {
        uint32_t log_n = 31 - __builtin_clz(n);
        rev.resize(n);
        wn.resize(n);
        for (uint32_t i = 0; i < n; ++i) {
            rev[i] = 0;
            for (uint32_t j = 0; j < log_n; ++j)
                if (i & (1 << j))
                    rev[i] |= (1 << (log_n - 1 - j));
        }
    }
}

void BigInt::mul(const BigInt &a, const BigInt& b, BigInt& res) const {
    uint32_t n = 1;
    while (n < std::max(a.getLength(), b.getLength())) n <<= 1;
    n <<= 1;
    fft::calcRev(n);
    array<ftype> fa(n);
    for (uint32_t i = 0; i < n; ++i)
        fa[i] = ftype(i < a.getLength() ? a.number[i] : 0, i < b.getLength() ? b.number[i] : 0);
    fft::fft(fa, n);
    for (uint32_t i = 0; i < n; ++i)
        fa[i] *= fa[i];
    fft::fft(fa, n);
    res.resize(n);
    res.number[0] = fa[0].im / (n << 1) + 0.5;
    for (uint32_t i = 1; i < n; ++i)
        res.number[i] = fa[n - i].im / (n << 1) + 0.5;
    std::uint64_t carry = 0;
    for (uint32_t i=0;i<n;++i) {
        res.number[i] += carry;
        carry = res.number[i] / base;
        res.number[i] %= base;
    }
    if (carry) res.number.pb(carry);
    while (res.getLength() > 1 && res.number[res.getLength()-1] == 0) res.number.pop();
}

void BigInt::set(const char *number) {
    if (*number == '-') pos = false, number++;
    else pos = true, number += (*number == '+');
    char* s = new char[strlen(number) + 1];
    strcpy(s, number);
    for (int32_t i=strlen(number);i>0;i-=6) {
        s[i] = 0;
        this->number.pb(atoll(i>=6?s+i-6:s));
    }
}

BigInt::BigInt(const char* number) {
    char* s = new char[strlen(number) + 1];
    strcpy(s, number);
    set(s);
    delete[] s;
}

BigInt::~BigInt() {}

void BigInt::resize(uint32_t newLength) {
    number.resize(newLength);
}

void BigInt::setSign(bool sign) {
    pos = sign;
}

void BigInt::set(const BigInt& n) {
    number.resize(n.getLength());
    for (uint32_t i = 0; i < getLength(); ++i)
        number[i] = n.number[i];
    setSign(n.getSign());
}

BigInt::BigInt(const BigInt& n) {
    set(n);
}

array<BigInt> stoi(array<char> password) {
    array<BigInt> res(password.getSize());
    for (uint32_t i = 0; i < password.getSize(); ++i) {
        BigInt tmp;
        tmp.set({password[i]+'0'});
        res[i] = tmp;
    }
}


void BigInt::div(const BigInt& dividend, const BigInt& divisor, BigInt& quotient, BigInt& remainder) {
//    assert(divisor > BigInt(base) && "Tolerance bound not reached");
    quotient.set("0"), remainder.set("0");
    if (dividend < divisor) {
        remainder.set(dividend);
        return;
    }
    quotient.resize(dividend.getLength());

    for (int32_t i = dividend.getLength() - 1; i >= 0; --i) {
        remainder *= base;
        remainder.number[0] = dividend.number[i];
        if (remainder >= divisor) {
            uint64_t l = 0, r = base;
            while (l < r) {
                uint64_t m = (l + r) >> 1;
                if (divisor * m <= remainder) l = m + 1;
                else r = m;
            }
            --l;
            remainder -= divisor * l;
            quotient.number[i] = l;
        }
    }
    while (quotient.getLength() > 1 && quotient.getNumber()[quotient.getLength()-1] == 0) quotient.number.pop();
}

void BigInt::div(const BigInt& dividend, const uint64_t& divisor, BigInt& quotient, uint64_t& remainder) {
    assert(divisor > 0 && "Division by zero not allowed");

    quotient.set("0");
    quotient.resize(dividend.getLength());
    remainder = 0;
    for (int32_t i = dividend.getLength() - 1; i >= 0; --i) {
        uint64_t cur = remainder * base + dividend.number[i];
        quotient.number[i] = cur / divisor;
        remainder = cur % divisor;
    }
    while (quotient.getLength() > 1 && quotient.getNumber()[quotient.getLength()-1] == 0) quotient.number.pop();
    quotient.setSign(dividend.getSign());
}

uint32_t BigInt::getLength() const {
    return this->number.getSize();
}

const array<uint64_t>& BigInt::getNumber() const {
    return this->number;
}

bool BigInt::getSign() const {
    return pos;
}

void BigInt::print() {
    if (!pos) std::cout << "-";
    printf("%llu", number[getLength()-1]);
    for (int32_t i=getLength()-2;i>=0;--i) printf("%06llu", number[i]);
    std::cout << "\n";
}

void BigInt::print(std::ostream &o) const {
    if (!pos) o << "-";
    o << number[getLength()-1];
    for (int32_t i=getLength()-2;i>=0;--i) {
        o.width(6);
        o.fill('0');
        o << number[i];
    }
}

void BigInt::mul(const BigInt &a, const uint64_t &b, BigInt &res) const {
    uint64_t carry = 0;
    for (uint32_t i=0; i < a.getLength() || carry; ++i) {
        if (i == res.getLength())
            res.number.pb(0);
        uint64_t cur = carry + (i < a.getLength() ? a.number[i] * b : 0);
        res.number[i] = cur % base;
        carry = cur/base;
    }
    while (res.getLength() > 1 && res.number[res.getLength()-1] == 0) res.number.pop();
}
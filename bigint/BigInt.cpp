//
// Created by nylon on 31.07.2023.
//

#include "BigInt.h"

BigInt::BigInt(): number(nullptr), length(0), pos(true) {}

BigInt::BigInt(const int64_t n) {
    BigInt(std::to_string(n).c_str());
}

namespace fft {
    std::int32_t *rev;
    ftype *wn;

    void fft(ftype *a, std::int32_t n, bool invert) {
        for (std::int32_t i = 0; i < n; ++i)
            if (i < rev[i])
                std::swap(a[i], a[rev[i]]);
        for (std::int32_t len=2;len<=n;len<<=1) {
            double ang = 2*pi/len*(invert ? -1 : 1);
            std::int32_t len2=len>>1;
            ftype w(cos(ang), sin(ang));
            wn[0] = ftype(1,0);
            for (std::int32_t i=1;i<len2;++i)
                wn[i] = wn[i-1]*w;
            for (std::int32_t i = 0; i < n; i += len) {
                ftype t(1, 0);
                for (std::int32_t j = 0; j < len2; ++j) {
                    t = wn[j] * a[i + j + len2];
                    ftype u = a[i + j];
                    a[i + j] = u + t;
                    a[i + j + len2] = u - t;
                }
            }
        }
        if (invert)
            for (std::int32_t i = 0; i < n; ++i)
                a[i] /= n;
    }

    void calcRev(std::int32_t n) {
        std::int32_t log_n = 31 - __builtin_clz(n);
        rev = new std::int32_t[n];
        wn = new ftype[n];
        for (std::int32_t i = 0; i < n; ++i) {
            rev[i] = 0;
            for (std::int32_t j = 0; j < log_n; ++j)
                if (i & (1 << j))
                    rev[i] |= (1 << (log_n - 1 - j));
        }
    }

    void dealloc() {
        delete[] rev;
        delete[] wn;
    }
}

void BigInt::mul(const BigInt &a, const BigInt& b, BigInt& res) const {
    std::int32_t n = 1;
    while (n < std::max(a.length, b.length)) n <<= 1;
    n <<= 1;
    fft::calcRev(n);
    ftype* fa = new ftype[n];
    ftype* fb = new ftype[n];
    for (int32_t i=0;i<n;++i)
        fa[i] = ftype((i<a.length)?a.number[i]:0, 0),
        fb[i] = ftype((i<b.length)?b.number[i]:0, 0);
    fft::fft(fa, n, false);
    fft::fft(fb, n, false);
    for (int32_t i=0;i<n;++i)
        fa[i] *= fb[i];
    fft::fft(fa, n, true);
    res.resize(n);
    for (int32_t i=0;i<n;++i)
        res.number[i] = (int32_t)(fa[i].re+0.5);
    std::int32_t carry = 0;
    for (int32_t i = 0; i < n; ++i)
        res.number[i] += carry,
        carry = res.number[i] / 10,
        res.number[i] %= 10;

    while (res.length > 1 && res.number[res.length-1] == 0)
        --res.length;

    delete[] fa; delete[] fb;
    fft::dealloc();
}

void BigInt::set(const char *number) {
    delete[] this->number;
    if (*number == '-') pos = false, number++;
    else pos = true, number += (*number == '+');
    length = strlen(number);
    this->number = new int32_t[length];
    for (int32_t i = 0; i < length; ++i)
        this->number[i] = number[length-1-i] - '0';
}

BigInt::BigInt(const char* number) {
    this->number = nullptr;
    set(number);
}

BigInt::~BigInt() {
    delete[] number;
}

void BigInt::resize(int32_t newLength) {
    auto* newArray = new int32_t[newLength];
    for (int32_t i = 0; i < newLength; ++i) {
        newArray[i] = (i < length) ? number[i] : 0;
    }
    delete[] number;
    number = newArray;
    length = newLength;
}

void BigInt::setSign(bool sign) {
    pos = sign;
}

void BigInt::set(const BigInt& n) {
    delete[] number;
    length = n.getLength();
    number = new int32_t[length];
    for (int32_t i = 0; i < length; ++i)
        number[i] = n.getNumber()[i];
    pos = n.getSign();
}

BigInt::BigInt(const BigInt& n) {
    set(n);
}

BigInt stoi(char* number) {
    // TODO: зашифровать строку и вернуть BigInt
}


void BigInt::div(const BigInt& dividend, const BigInt& divisor, BigInt& quotient, BigInt& remainder) {
    assert(divisor != BigInt("0") && "Division by zero not allowed");

    quotient.set("0");
    remainder.set(dividend);
    while (remainder >= divisor) {
        remainder -= divisor;
        quotient += BigInt("1");
    }
}

int32_t BigInt::getLength() const {
    return this->length;
}

int32_t* BigInt::getNumber() const {
    return this->number;
}

bool BigInt::getSign() const {
    return pos;
}

void BigInt::print() {
    if (!pos) std::cout << "-";
    for (int32_t i=length-1;i>=0;--i) std::cout << number[i];
    std::cout << "\n";
}
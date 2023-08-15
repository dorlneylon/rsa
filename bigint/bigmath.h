//
// Created by nylon on 04.08.2023.
//

#ifndef BIGMATH_H
#define BIGMATH_H

#include "BigInt.h"

namespace bm {
    BigInt& abs(BigInt&);
    BigInt power(const BigInt&, const BigInt&);
    BigInt mulmod(const BigInt&, const BigInt&, const BigInt&);
    BigInt powmod(const BigInt&, const BigInt&, const BigInt&);
    BigInt gcd(const BigInt&, const BigInt&);
    BigInt gcdex(const BigInt&, const BigInt&, BigInt&, BigInt&);
    BigInt inverse(const BigInt&, const BigInt&);
    BigInt sqrt(const BigInt&);
    void transform(const BigInt&, BigInt&, BigInt&);
    uint64_t powmod(int32_t, int32_t, int32_t);
    BigInt random(const BigInt&, const BigInt&);
} // namespace bm

#endif //BIGMATH_H

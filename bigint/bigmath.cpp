//
// Created by nylon on 04.08.2023.
//

#include "bigmath.h"

namespace bm {
    BigInt& abs(BigInt& a) {
        if (!a.getSign()) a.set(-a);
        return a;
    }

    BigInt power(const BigInt& a, const BigInt& p) {
        assert(p.getSign() && "Power must be positive");
        BigInt res("1");
        BigInt tmp; tmp.set(a);
        BigInt tmpP; tmpP.set(p);
        while (tmpP > BigInt("0")) {
            if (tmpP % BigInt("2") == BigInt("1"))
                res *= tmp;
            tmp *= tmp;
            tmpP /= BigInt("2");
        }
        return res;
    }

    BigInt random(const BigInt& left_bound, const BigInt& right_bound) {
        assert(left_bound < right_bound && "Left bound must be less than right bound");
        BigInt tmp = BigInt(std::to_string((int64_t)malloc(sizeof(int32_t))).c_str());
        return left_bound + tmp % (right_bound-left_bound);
    }

    uint64_t powmod(int32_t a, int32_t b, int32_t p) {
        uint64_t res = 1;
        while (b)
            if (b & 1) res = (uint64_t)(res*1ll*a%p), --b;
            else a = (int32_t)(a*1ll*a%p), b >>= 1;
        return res;
    };

    BigInt powmod(const BigInt& a, const BigInt& p, const BigInt& m) {
        assert(p.getSign() && "Power must be positive");
        BigInt res("1");
        BigInt tmp = a, tmpP = p;
        while (tmpP > BigInt("0")) {
            if (tmpP % BigInt("2") == BigInt("1"))
                res = (res * tmp) % m;
            tmp = (tmp * tmp) % m;
            tmpP /= BigInt("2");
        }
        return res;
    }
} // namespace bm
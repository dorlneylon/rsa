//
// Created by nylon on 04.08.2023.
//

#include "PrimeHandler.h"
#include "../bigint/bigmath.h"

BigInt PrimeHandler::takeRandom(const uint64_t n) {
    BigInt  bp = BigInt(std::to_string(n-1).c_str());
    BigInt  tmp = bm::power(BigInt("2"),bp);
    BigInt  min = tmp+BigInt("1"),
            max = bm::power(BigInt("2"),BigInt(std::to_string(n).c_str()))-BigInt("1");
//    BigInt res; res.set(bm::random(min, max));
    return bm::random(min, max);
}

BigInt PrimeHandler::getPotentialPrime(const uint64_t n) {
    while (true) {
        BigInt tmp = takeRandom(n);
        bool f = false;
        if (tmp.getNumber()[0]%2 == 0) continue;
        for (const int32_t& d : primes)
            if (tmp % BigInt(std::to_string(d).c_str()) == BigInt("0")) {
                f = true;
                break;
            }
        if (!f) return tmp;
    }
}

bool PrimeHandler::getMillerRabinPrime(const BigInt &a) {
    uint64_t power_of_two = 0;
    BigInt tmp = a - 1;
    while ((tmp /= BigInt("2")).getSign()) power_of_two++;
    BigInt d = (a - 1) / bm::power(BigInt("2"), BigInt(std::to_string(power_of_two).c_str()));
    return bm::powmod(a, d, a) == BigInt("1");
}

BigInt& PrimeHandler::getPrime(const uint64_t n) {
    BigInt candidate = getPotentialPrime(n);
    for (uint32_t i=0;i<30;++i) if (!getMillerRabinPrime(candidate)) return candidate = BigInt("-1");
    return candidate;
}

int32_t PrimeHandler::getPrimitiveRoot(int32_t mod) {
    int32_t phi = mod - 1, cnt = 0, n = phi;
    int32_t* fact = new int32_t[mod];
    for (int32_t k=2;k*k<=n;++k) {
        if (n%k == 0) {
            fact[cnt++] = k;
            while (n%k == 0) n /= k;
        }
    }
    if (n > 1) fact[cnt++] = n;

    bool ok;
    int32_t res = 2;
    for (;res<=mod;++res) {
        ok = true;
        for (int32_t i=0;i<cnt&&ok;++i)
            ok &= bm::powmod(res, phi/fact[i], mod) != 1;
        if (ok) break;
    }
    delete[] fact;
    if (ok) return res;
    return -1;
}
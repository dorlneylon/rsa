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
    return bm::random(min, max);
}

BigInt PrimeHandler::getPotentialPrime(const uint64_t n) {
    while (true) {
        BigInt tmp = takeRandom(n);
        bool f = false;
        for (const auto& d : primes)
            if (tmp % d == 0) {
                f = true;
                break;
            }
        if (!f) return tmp;
    }
}

bool PrimeHandler::getMillerRabinPrime(const BigInt &n, BigInt& a) {
    // n is being tested, a is a parameter
    assert(n > 1 && "Number must be greater than 1");
    if (n.getNumber()[0]%2==0) return n == BigInt("2");

    if (a < BigInt("2")) a = BigInt("2");
    for (BigInt g; (g = bm::gcd(a, n)) != BigInt("1"); a += BigInt("1"))
        if (n > g) return false;

    BigInt n_1 = n - BigInt("1");
    BigInt p,q;
    bm::transform(n_1, p, q);

    BigInt rem = bm::powmod(a, q, n);
    if (rem == BigInt("1") || rem == n_1) return true;

    for (BigInt i=BigInt("1"); i<p; i+=BigInt("1")) {
        rem = (rem*rem)%n;
        if (rem == n_1) return true;
        if (rem == BigInt("1")) return false;
    }
    return false;
}

bool PrimeHandler::_mlr(const BigInt &n, BigInt &a) {
    return getMillerRabinPrime(n,a);
}

bool PrimeHandler::goHardTest(BigInt &n) {
    BigInt a = BigInt("2"), sqrt = bm::sqrt(n);
    for (;a<=sqrt;a+=BigInt("1"))
        if (n%a == BigInt("0")) return false;
    return true;
}

BigInt PrimeHandler::getPrime(const uint64_t n) {
    BigInt candidate = getPotentialPrime(n);
    for (uint8_t i=0;i<30;++i) {
        BigInt parameter = bm::random(BigInt("2"), candidate-BigInt("2"));
        if (!getMillerRabinPrime(candidate, parameter)) return getPrime(n);
    }
    if (!goHardTest(candidate)) return getPrime(n);
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
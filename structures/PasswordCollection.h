//
// Created by nylon on 13.08.2023.
//

#ifndef PASSWORDCOLLECTION_H
#define PASSWORDCOLLECTION_H
#include "../bigint/BigInt.h"
#include "../bigint/bigmath.h"
#include <set>

class PasswordCollection : public std::multiset<BigInt> {
public:
    PasswordCollection();
    PasswordCollection(const BigInt&, const BigInt&, const BigInt&);
    void add(const BigInt&);
    void remove(const BigInt&);
    bool contains(const BigInt&) const;
    void set(const PasswordCollection&);
    PasswordCollection& operator=(const PasswordCollection&);
    void setKeys(const BigInt&, const BigInt&, const BigInt&);
    ~PasswordCollection();
private:
    BigInt N, E, D;
    BigInt encrypt(const BigInt&) const;
    BigInt encrypt(const BigInt&, const BigInt&, const BigInt&) const;
    BigInt decrypt(const BigInt&) const;
    BigInt decrypt(const BigInt&, const BigInt&, const BigInt&) const;
    BigInt reEncrypt(const BigInt&) const;
};


#endif //PASSWORDCOLLECTION_H

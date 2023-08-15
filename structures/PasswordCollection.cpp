//
// Created by nylon on 13.08.2023.
//

#include "PasswordCollection.h"

PasswordCollection::PasswordCollection(): N(BigInt("0")), E(BigInt("0")), D(BigInt("0")) {}
PasswordCollection::PasswordCollection(const BigInt& _N, const BigInt& _E, const BigInt& _D): N(_N), E(_E), D(_D) {}

void PasswordCollection::add(const BigInt& a) {
    this->insert(encrypt(a));
}

void PasswordCollection::remove(const BigInt& a) {
    this->erase(encrypt(a));
}

bool PasswordCollection::contains(const BigInt& a) const {
    return this->find(encrypt(a))!=this->end();
}

void PasswordCollection::set(const PasswordCollection& a) {
    this->clear();
    this->insert(a.begin(),a.end());
}

PasswordCollection& PasswordCollection::operator=(const PasswordCollection& a) {
    this->set(a);
    return *this;
}

void PasswordCollection::setKeys(const BigInt& _N, const BigInt& _E, const BigInt& _D) {
    for (auto& k: *this) {
        BigInt tmp = decrypt(k);
        remove(k);
        add(encrypt(tmp,_N,_E));
    }
}

BigInt PasswordCollection::encrypt(const BigInt& a) const {
    return bm::powmod(a,E,N);
}

BigInt PasswordCollection::encrypt(const BigInt& a, const BigInt& _N, const BigInt& _E) const {
    return bm::powmod(a,_E,_N);
}

BigInt PasswordCollection::decrypt(const BigInt& a, const BigInt& _N, const BigInt& _D) const {
    return bm::powmod(a,_D,_N);
}

BigInt PasswordCollection::decrypt(const BigInt& a) const {
    return bm::powmod(a,D,N);
}

BigInt PasswordCollection::reEncrypt(const BigInt& a) const {
    return encrypt(decrypt(a));
}

PasswordCollection::~PasswordCollection() {}
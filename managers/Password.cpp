//
// Created by nylon on 31.07.2023.
//

#include "Password.h"

Password::Password(array<char> p, array<char> l, array<char> s): password(p), login(l), service(s) {
    setModifyDate(new Date());
}

void Password::setPassword(array<char> &p) {
    execute([&](){password = p;});
}

void Password::setLogin(array<char> &l) {
    execute([&](){login = l;});
}

void Password::setService(array<char> &s) {
    execute([&](){service = s;});
}

array<char> &Password::getPassword() {
    decode();
    return password;
}

array<char> &Password::getLogin() {
    return login;
}

array<char> &Password::getService() {
    return service;
}

Date *Password::getModifyDate() {
    return modifyDate;
}

void Password::setModifyDate(const Date *d) {
    modifyDate = new Date(*d);
}

Password::~Password() {
    delete modifyDate;
}

void Password::decode() {
    // todo
}
//
// Created by nylon on 31.07.2023.
//

#ifndef PASSWORD_H
#define PASSWORD_H
#include "Date.h"
#include "../structures/array.h"

class Password {
public:
    Password(array<char> p = {}, array<char> l = {}, array<char> s = {});
    void setPassword(array<char>&);
    void setLogin(array<char>&);
    void setService(array<char>&);
    array<char>& getPassword();
    array<char>& getLogin();
    array<char>& getService();
    Date* getModifyDate();
    void setModifyDate(const Date*);
    ~Password();
private:
    array<char> password, login, service;
    void decode();
    template <typename F>
    void execute(F f) {
        f();
        setModifyDate(new Date());
    }
    Date* modifyDate;
};


#endif //PASSWORD_H

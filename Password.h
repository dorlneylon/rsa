//
// Created by nylon on 31.07.2023.
//

#ifndef PASSWORD_H
#define PASSWORD_H
#include "Date.h"

class Password {
public:
    Password();
    Password(const char*, const char*, const char*);
    void setPassword(const char*);
    void setLogin(const char*);
    void setService(const char*);
    char* getPassword();
    char* getLogin();
    char* getService();
    Date* getModifyDate();
    void setModifyDate(const Date*);
    ~Password();
private:
    char* password, *login, *service;
    Date* modify_date;
};


#endif //PASSWORD_H

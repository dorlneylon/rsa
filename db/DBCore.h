//
// Created by nylon on 13.08.2023.
//

#ifndef DBCORE_H
#define DBCORE_H
#include <pqxx/pqxx>

class DBCore {
public:
    DBCore();
    ~DBCore();
    void connect();
    void disconnect();
//    void createTable();
    bool execute(const std::string&);
    std::string select(const std::string&);
    bool contains(const std::string&);
    void clear();
    void print();
//    print(const char*);
private:
    void establish_connection();
    void close_connection();

    pqxx::connection* connection;
    pqxx::work* work;
    pqxx::result* result;
    std::string host = "localhost";
    std::string port = "5432";
    std::string dbname = "postgres";
    std::string user = "nylon";
    std::string password = "";
};


#endif //DBCORE_H

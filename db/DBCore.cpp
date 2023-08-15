//
// Created by nylon on 13.08.2023.
//

#include "DBCore.h"

DBCore::DBCore() {
    connect();
}

DBCore::~DBCore() {
    disconnect();
}

void DBCore::connect() {
    try {
        establish_connection();
    } catch (const std::exception& e) {
        printf("Error connecting to database: %s\n", e.what());
    }
}

void DBCore::establish_connection() {
    std::string connection_string = "host=" + host + " port=" + port +
                                    " dbname=" + dbname + " user=" + user + " password=" + password;
    try {
        connection = new pqxx::connection(connection_string);
        if (connection->is_open())
            printf("Opened database successfully: %s\n", connection->dbname());
        else
            printf("Can't open database\n");
    } catch (const std::exception& e) {
        printf("Error opening database: %s\n", e.what());
    }
}

std::string DBCore::select(const std::string &s) {
    std::string res;
    try {
        work = new pqxx::work(*connection);
        result = new pqxx::result(work->exec(s));
        if (result->size() == 0)
//            printf("Nothing found\n");
            return "";
        res = result->at(0).at(0).as<std::string>();
        work->commit();
    } catch (const std::exception& e) {
        printf("Error selecting from database: %s\n", e.what());
    }
    return res;
}

void DBCore::disconnect() {
    try {
        close_connection();
    } catch (const std::exception& e) {
        printf("Error disconnecting from database: %s\n", e.what());
    }
}

void DBCore::close_connection() {
    connection->close();
    printf("Closed database successfully\n");
}

bool DBCore::execute(const std::string &q) {
    try {
        work = new pqxx::work(*connection);
        work->exec(q);
        work->commit();
    } catch (const std::exception& e) {
        printf("Error executing query: %s\n", e.what());
        return false;
    }
    return true;
}

bool DBCore::contains(const std::string &s) {
    std::string res = select("SELECT * FROM passwords WHERE password = '" + s + "';");
    return res != "";
}

void DBCore::clear() {
    execute("DELETE FROM passwords;");
}

void print(const char* s) {
    printf("%s\n", s);
}

void DBCore::print() { // debug
    printf("Table:\n");
    try {
        work = new pqxx::work(*connection);
        result = new pqxx::result(work->exec("SELECT * FROM passwords;"));
        for (auto row: *result) {
            for (auto field: row)
                printf("%s\t", field.c_str());
            printf("\n");
        }
        work->commit();
    } catch (const std::exception& e) {
        printf("Error printing table: %s\n", e.what());
    }
}
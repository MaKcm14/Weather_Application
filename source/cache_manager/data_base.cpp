// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "include/data_base.h"

NDataBase::TPostgreSql::TPostgreSql(const std::string& ip, const std::string& port, const std::string& password) {
    try {
        Connection = PQsetdbLogin(ip.c_str(), port.c_str(), nullptr, nullptr, "postgres", "postgres", 
            password.substr(1, password.size() - 2).c_str());

        if (PQstatus(Connection) == CONNECTION_BAD) {
            throw TDataBaseException("connection to the DB wasn't set correctly");
        } 

    } catch (std::exception& excp) {
        throw TDataBaseException(excp.what()); 
    }
}


std::vector<std::vector<std::string>> NDataBase::TPostgreSql::ISelect(const std::string& query) {
    std::vector<std::vector<std::string>> data;
    auto result = PQexec(Connection, query.c_str());

    if (PQresultStatus(result) == PGRES_FATAL_ERROR || PQresultStatus(result) == PGRES_NONFATAL_ERROR) {
        PQclear(result);
        throw TDataBaseException("error while the processing the 'SELECT' query");
    }

    if (PQntuples(result)) {
        for (size_t i = 0; i != PQntuples(result); ++i) {
            data.push_back({});
            for (size_t j = 0; j != PQnfields(result); ++j) {
                data[i].push_back(PQgetvalue(result, i, j));
            }
        }
    }

    PQclear(result);
    
    return data;
}


void NDataBase::TPostgreSql::IInsert(const std::string& query) {
    auto result = PQexec(Connection, query.c_str());

    if (PQresultStatus(result) == PGRES_FATAL_ERROR || PQresultStatus(result) == PGRES_NONFATAL_ERROR) {
        PQclear(result);
        throw TDataBaseException("error while the processing the 'INSERT' query");
    }

    PQclear(result);
}


void NDataBase::TPostgreSql::IUpdate(const std::string& query) {
    auto result = PQexec(Connection, query.c_str());

    if (PQresultStatus(result) == PGRES_FATAL_ERROR || PQresultStatus(result) == PGRES_NONFATAL_ERROR) {
        PQclear(result);
        throw TDataBaseException("error while the processing the 'UPDATE' query");
    }

    PQclear(result);
}


void NDataBase::TPostgreSql::IDelete(const std::string& query) {
    auto result = PQexec(Connection, query.c_str());

    if (PQresultStatus(result) == PGRES_FATAL_ERROR || PQresultStatus(result) == PGRES_NONFATAL_ERROR) {
        PQclear(result);
        throw TDataBaseException("error while the processing the 'DELETE' query");
    }

    PQclear(result);
}


void NDataBase::TPostgreSql::ICreateTable(const std::string& query) {
    auto result = PQexec(Connection, query.c_str());

    if (PQresultStatus(result) == PGRES_FATAL_ERROR || PQresultStatus(result) == PGRES_NONFATAL_ERROR) {
        PQclear(result);
        throw TDataBaseException("error while the processing the 'CREATE TABLE' query");
    }

    PQclear(result);
}
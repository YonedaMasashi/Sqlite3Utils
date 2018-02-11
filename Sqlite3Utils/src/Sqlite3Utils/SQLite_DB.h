#pragma once

#include <iostream>
#include <memory>

#include "sqlite3.h"

class SQLite_Error;

using namespace std;

class SQLite_Statement;

class SQLite_DB
{
public:
	SQLite_DB();
	~SQLite_DB();

public:
	void openDatabase(const string& dbPath);
	void closeDatabase();
	void executeSql(const string& sql);
	void begin();
	void commit();
	SQLite_Statement* prepared(const string& sql);
	void executeStatement(SQLite_Statement* statement);

private:
	sqlite3* database;

};


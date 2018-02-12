#pragma once

#include <functional>
#include <iostream>

using namespace std;

class SQLite_DB;

class TestExecutor
{
public:
	TestExecutor();
	~TestExecutor();

public:
	static void execute(function<void(SQLite_DB&)> testFunction, string dbName, SQLite_DB& sqLiteDb);
};


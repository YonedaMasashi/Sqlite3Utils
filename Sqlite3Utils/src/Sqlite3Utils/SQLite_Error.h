#pragma once

#include <iostream>

#include "sqlite3.h"

using namespace std;

class SQLite_Error
{
public:
	SQLite_Error(int errorCode, string addMsg);
	SQLite_Error(sqlite3* database, string addMsg);
	~SQLite_Error();

public:
	static void checkError(int errorCode, string addMsg);
	static void checkError(sqlite3* database, string addMsg);

	bool isError();
	string getErrorMessage();

private:
	int errorCode;
	string errorMessage;
};


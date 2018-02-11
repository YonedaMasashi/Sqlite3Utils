#pragma once

#include <iostream>
#include <memory>

#include "sqlite3.h"

class SQLite_Error;

using namespace std;

class SQLite_Statement
{
public:
	SQLite_Statement(sqlite3_stmt* statement);
	~SQLite_Statement();

public:
	void execute();

	void finalize();

	void reset();
	void clear();

	void bindInt(int index, int value);
	void bindDouble(int index, double value);
	void bindText(int index, string value);
	void bindBlob(int index, const void* value, int size);

	int columnCount();

private:
	sqlite3_stmt* statement;

};


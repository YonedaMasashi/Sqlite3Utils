#pragma once

#include <iostream>
#include <memory>

#include "sqlite3.h"

class SQLite_Error;

using namespace std;

class SQLite_Statement
{
public:
	SQLite_Statement(sqlite3_stmt* statement, string sql);
	~SQLite_Statement();

public:
	// ñﬂÇËíl(éÂÇ… select ï∂ÇÃé¿çsóp true: exist any data, false: no data);
	bool step();

	void finalize();

	void reset();
	void clear();

	void bindInt(int index, int value);
	void bindDouble(int index, double value);
	void bindText(int index, string value);
	void bindBlob(int index, const void* value, int size);

	int columnCount();

	// The leftmost column is number 0.
	string getColumnName(int columnIndex);

	// The leftmost column of the result set has the index 0.
	int getInt(int columnIndex);
	

private:
	string currentSql;
	sqlite3_stmt* statement;

};


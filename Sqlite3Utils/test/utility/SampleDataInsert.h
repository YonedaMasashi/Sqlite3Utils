#pragma once

#include <functional>
#include <iostream>

using namespace std;

class SQLite_DB;

class SampleDataInsert
{
public:
	SampleDataInsert();
	~SampleDataInsert();

public:
	static void execute(SQLite_DB& sqLiteDb);
};


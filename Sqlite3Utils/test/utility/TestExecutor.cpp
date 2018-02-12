#include "stdafx.h"

#include "CppUnitTest.h"

#include "utility/TestExecutor.h"
#include "Sqlite3Utils/SQLite_Error.h"
#include "Sqlite3Utils/SQLite_DB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TestExecutor::TestExecutor()
{
}


TestExecutor::~TestExecutor()
{
}

void TestExecutor::execute(function<void(SQLite_DB&)> testFunction, string dbName, SQLite_DB& sqLiteDb)
{
	SQLite_Error* error = 0;
	remove(dbName.c_str());
	try {
		sqLiteDb.openDatabase(dbName);
		testFunction(sqLiteDb);
	}
	catch (SQLite_Error& e) {
		error = &e;
	}
	Assert::IsNull(error);
	try {
		sqLiteDb.closeDatabase();
	}
	catch (SQLite_Error& e) {
		error = &e;
	}
}

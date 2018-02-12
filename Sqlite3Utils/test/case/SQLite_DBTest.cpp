#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <functional>

#include "Sqlite3Utils/SQLite_DB.h"
#include "Sqlite3Utils/SQLite_Error.h"

#include "utility/TestExecutor.h"

namespace Sqlite3UtilsUnitTest
{		
	TEST_CLASS(SQLite_DBTest)
	{
	public:

		TEST_METHOD(SQLite_DBTest_Open)
		{
			string dbName = "test_db.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				},
				dbName,
				sqliteDb);
		}

		TEST_METHOD(SQLite_DBTest_CreateTable)
		{
			string dbName = "test_db2.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				string sql = "CREATE TABLE TESTTBL("
					"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";
				sqliteDb.executeSql(sql);
				},
				dbName,
				sqliteDb);
		}

		TEST_METHOD(SQLite_DBTest_DB_DeleteTable) 
		{
			string dbName = "test_db3.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				string sql = "CREATE TABLE TESTTBL("
					"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";
				sqliteDb.executeSql(sql);

				sql = "DELETE FROM TESTTBL;";
				sqliteDb.executeSql(sql);
				},
				dbName,
				sqliteDb);
		}
	};
}

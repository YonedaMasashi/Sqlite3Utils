#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Sqlite3Utils/SQLite_DB.h"
#include "Sqlite3Utils/SQLite_Error.h"

namespace Sqlite3UtilsUnitTest
{		
	TEST_CLASS(SQLite_DBTest)
	{
	public:

		TEST_METHOD(SQLite_DBTest_Open)
		{
			string dbName = "test_db.db";
			SQLite_DB hoge;
			SQLite_Error* error = 0;
			try {
				hoge.openDatabase(dbName);
			}
			catch (SQLite_Error& e) {
				error = &e;
			}

			Assert::IsNull(error);

			hoge.closeDatabase();
			remove(dbName.c_str());
		}

		TEST_METHOD(SQLite_DBTest_CreateTable)
		{
			string dbName = "test_db2.db";
			string sql = "CREATE TABLE TESTTBL("
				"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";

			SQLite_DB hoge;
			SQLite_Error* error = 0;
			try {
				hoge.openDatabase(dbName);
				hoge.executeSql(sql);
			}
			catch (SQLite_Error& e) {
				error = &e;
			}
			Assert::IsNull(error);
			hoge.closeDatabase();
			remove(dbName.c_str());
		}

		TEST_METHOD(SQLite_DBTest_DB_DeleteTable) {
			string dbName = "test_db3.db"; 

			string sql = "CREATE TABLE TESTTBL("
				"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";

			SQLite_DB hoge;
			SQLite_Error* error = 0;
			try {
				hoge.openDatabase(dbName);
				hoge.executeSql(sql);

				sql = "DELETE FROM TESTTBL;";
				hoge.executeSql(sql);

			}
			catch (SQLite_Error& e) {
				error = &e;
			}
			Assert::IsNull(error);
			hoge.closeDatabase();
			remove(dbName.c_str());
		}
	};
}

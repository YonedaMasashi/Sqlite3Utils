#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Sqlite3Utils/SQLite_DB.h"
#include "Sqlite3Utils/SQLite_Statement.h"
#include "Sqlite3Utils/SQLite_Error.h"

namespace SQLite_StatementTest
{
	TEST_CLASS(SQLite_StatementTest)
	{
	public:

		TEST_METHOD(InsertTest)
		{
			string dbName = "InsertTest.db";
			remove(dbName.c_str());

			SQLite_DB hoge;
			SQLite_Error* error = 0;
			string sql = "CREATE TABLE TESTTBL("
				"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";

			SQLite_Statement* stmt = 0;

			try {
				hoge.openDatabase(dbName);
				hoge.executeSql(sql);

				stmt = hoge.prepared("INSERT INTO TESTTBL(VAL1, VAL2) VALUES(?, ?);");
				for (int idx = 0; idx < 100; idx++) {
					stmt->bindInt(1, idx + 100);
					if (idx % 2 == 0) {
						stmt->bindInt(2, idx + 1000);
					}
					hoge.executeStatement(stmt);

					stmt->reset();
					stmt->clear();
				}
				long long rowId = hoge.getLastInsertRowId();
				Assert::AreEqual(100L, (long)rowId);
			} 
			catch (SQLite_Error& e) {
				error = &e;
			}
			if (stmt != 0) {
				stmt->finalize();
			}
			Assert::IsNull(error);
			hoge.closeDatabase();
		}
	};
}

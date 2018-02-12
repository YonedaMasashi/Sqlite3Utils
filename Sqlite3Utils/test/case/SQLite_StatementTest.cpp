#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Sqlite3Utils/SQLite_DB.h"
#include "Sqlite3Utils/SQLite_Statement.h"
#include "Sqlite3Utils/SQLite_Error.h"

#include "utility/TestExecutor.h"
#include "utility/SampleDataInsert.h"

namespace SQLite_StatementTest
{
	TEST_CLASS(SQLite_StatementTest)
	{
	public:

		TEST_METHOD(InsertTest)
		{
			string dbName = "InsertTest.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				SampleDataInsert::execute(sqliteDb);

				long long rowId = sqliteDb.getLastInsertRowId();
				Assert::AreEqual(100L, (long)rowId);

				},
				dbName,
				sqliteDb);
		}

		TEST_METHOD(SelectTest) {
			string dbName = "SelectTest.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				SampleDataInsert::execute(sqliteDb);

				string prepareSql = "SELECT IDX, VAL1, VAL2 FROM TESTTBL ORDER BY IDX;";
				SQLite_Statement* stmt = sqliteDb.prepared(prepareSql);
				stmt->step();
				int colCount = stmt->columnCount();
				Assert::AreEqual(3, colCount);
				Assert::AreEqual("IDX", stmt->getColumnName(0).c_str());
				Assert::AreEqual("VAL1", stmt->getColumnName(1).c_str());
				Assert::AreEqual("VAL2", stmt->getColumnName(2).c_str());

				Assert::AreEqual(1, stmt->getInt(0));

				stmt->reset();
				stmt->clear();

				},
				dbName,
				sqliteDb);
		}

		TEST_METHOD(SelectTest_OutOfIndex) {
			string dbName = "SelectOutOfIndexTest.db";
			SQLite_DB sqliteDb;

			TestExecutor::execute(
				[&](SQLite_DB& sqliteDb) {
				SampleDataInsert::execute(sqliteDb);

				string prepareSql = "SELECT IDX, VAL1, VAL2 FROM TESTTBL ORDER BY IDX;";
				SQLite_Statement* stmt = sqliteDb.prepared(prepareSql);

				for (int i = 0; i < 100; ++i) {
					stmt->step();
					Assert::AreEqual(i + 1, stmt->getInt(0));
				}
				Assert::AreEqual(false, stmt->step());

				stmt->reset();
				stmt->clear();

				},
				dbName,
				sqliteDb);
		}

	};
}

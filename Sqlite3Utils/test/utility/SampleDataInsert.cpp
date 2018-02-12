#include "stdafx.h"

#include "CppUnitTest.h"

#include "utility/SampleDataInsert.h"
#include "Sqlite3Utils/SQLite_Statement.h"
#include "Sqlite3Utils/SQLite_DB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

SampleDataInsert::SampleDataInsert()
{
}


SampleDataInsert::~SampleDataInsert()
{
}

void SampleDataInsert::execute(SQLite_DB& sqLiteDb)
{
	string sql = "CREATE TABLE TESTTBL("
		"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);";
	SQLite_Statement* stmt = 0;
	sqLiteDb.executeSql(sql);

	stmt = sqLiteDb.prepared("INSERT INTO TESTTBL(VAL1, VAL2) VALUES(?, ?);");
	for (int idx = 0; idx < 100; idx++) {
		stmt->bindInt(1, idx + 100);
		if (idx % 2 == 0) {
			stmt->bindInt(2, idx + 1000);
		}
		stmt->execute();

		stmt->reset();
		stmt->clear();
	}
	if (stmt != 0) {
		stmt->finalize();
	}
}

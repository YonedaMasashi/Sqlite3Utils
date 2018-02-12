#include "Sqlite3Utils/SQLite_DB.h"

#include "Sqlite3Utils/SQLite_Error.h"
#include "Sqlite3Utils/SQLite_Statement.h"

SQLite_DB::SQLite_DB()
{
}


SQLite_DB::~SQLite_DB()
{
}

void SQLite_DB::openDatabase(const string & dbPath)
{
	SQLite_Error::checkError(
		sqlite3_open(dbPath.c_str(), &database)
		, ("openDatabase:" + dbPath)
	);
}

void SQLite_DB::closeDatabase()
{
	SQLite_Error::checkError(
		sqlite3_close(database),
		"closeDatabase"
	);
}

void SQLite_DB::executeSql(const string& sql) 
{
	SQLite_Error::checkError(
		sqlite3_exec(
			database,
			sql.c_str(),
			NULL, NULL, NULL),
		("executeSql" + sql)
	);
}

void SQLite_DB::begin()
{
	SQLite_Error::checkError(
		sqlite3_exec(database, "BEGIN;", NULL, NULL, NULL),
		"begin"
	);
}

void SQLite_DB::commit()
{
	SQLite_Error::checkError(
		sqlite3_exec(database, "COMMIT;", NULL, NULL, NULL),
		"commit"
	);
}

SQLite_Statement* SQLite_DB::prepared(const string& sql)
{
	// If the nByte argument (third argument) is negative, then zSql is read up to the first zero terminator. 
	sqlite3_stmt* stm = NULL;
	SQLite_Error::checkError(
		sqlite3_prepare(database, sql.c_str(), -1, &stm, NULL),
		"prepared database error:" + sql
	);
	if (stm == NULL) {
		SQLite_Error error(database, "prepared stm null:" + sql);
		throw error;
	}

	SQLite_Statement* pSQLite_Statement = new SQLite_Statement(stm, sql);
	return pSQLite_Statement;
}

long long SQLite_DB::getLastInsertRowId() 
{
	return sqlite3_last_insert_rowid(this->database);
}
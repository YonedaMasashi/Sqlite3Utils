#include "Sqlite3Utils/SQLite_Statement.h"

#include "Sqlite3Utils/SQLite_Error.h"


SQLite_Statement::SQLite_Statement(sqlite3_stmt* statement)
{
	this->statement = statement;
}

SQLite_Statement::~SQLite_Statement()
{
}

void SQLite_Statement::execute()
{
	int errCode = sqlite3_step(this->statement);
	if (errCode != SQLITE_DONE) {
		SQLite_Error error(errCode, "SQLite_Statement::execute");
		throw error;
	}
}

void SQLite_Statement::finalize()
{
	sqlite3_finalize(this->statement);
}

void SQLite_Statement::reset()
{
	SQLite_Error::checkError(
		sqlite3_reset(this->statement),
		"SQLite_Statement::reset(sqlite3_reset)"
	);

	SQLite_Error::checkError(
		sqlite3_clear_bindings(this->statement),
		"SQLite_Statement::reset(sqlite3_clear_bindings)"
	);
}

void SQLite_Statement::clear()
{
	SQLite_Error::checkError(
		sqlite3_clear_bindings(this->statement),
		"SQLite_Statement::clear()"
	);
}

void SQLite_Statement::bindInt(int index, int value) {
	sqlite3_bind_int(statement, index, value);
}

void SQLite_Statement::bindDouble(int index, double value) {
	sqlite3_bind_double(statement, index, value);
}

void SQLite_Statement::bindText(int index, string value) {
	sqlite3_bind_text(statement, index, value.c_str(), (int)value.length(), SQLITE_TRANSIENT);
}

void SQLite_Statement::bindBlob(int index, const void* value, int size) {
	sqlite3_bind_blob(statement, index, value, size, SQLITE_TRANSIENT);
}

int SQLite_Statement::columnCount() {
	return sqlite3_column_count(statement);
}

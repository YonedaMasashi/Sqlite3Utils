#include "Sqlite3Utils/SQLite_Statement.h"

#include "Sqlite3Utils/SQLite_Error.h"


SQLite_Statement::SQLite_Statement(sqlite3_stmt* statement, string sql)
{
	currentSql = sql;
	this->statement = statement;
}

SQLite_Statement::~SQLite_Statement()
{
}

bool SQLite_Statement::step() {
	int errCode = sqlite3_step(this->statement);
	if (errCode == SQLITE_ROW) {
		return true;
	}

	// SQLITE_DONE ‚ª‹A‚Á‚Ä‚­‚é‚Í‚¸‚¾‚ªA”O‚Ì‚½‚ß OK ‚à
	if (errCode == SQLITE_OK || errCode == SQLITE_DONE) {
		return false;
	}
	SQLite_Error error(errCode, "SQLite_Statement::step\n  currentSql:" + currentSql);
	throw error;
}

void SQLite_Statement::finalize()
{
	sqlite3_finalize(this->statement);
}

void SQLite_Statement::reset()
{
	SQLite_Error::checkError(
		sqlite3_reset(this->statement),
		"SQLite_Statement::reset(sqlite3_reset)\n  currentSql:" + currentSql
	);

	SQLite_Error::checkError(
		sqlite3_clear_bindings(this->statement),
		"SQLite_Statement::reset(sqlite3_clear_bindings)\n  currentSql:" + currentSql
	);
}

void SQLite_Statement::clear()
{
	SQLite_Error::checkError(
		sqlite3_clear_bindings(this->statement),
		"SQLite_Statement::clear()\n  currentSql:" + currentSql
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

string SQLite_Statement::getColumnName(int columnIndex) {
	const char* columneName = sqlite3_column_name(statement, columnIndex);
	return (reinterpret_cast<char const *>(columneName));
}

int SQLite_Statement::getInt(int columnIndex) {
	return sqlite3_column_int(statement, columnIndex);
}

#include "Sqlite3Utils/SQLite_Error.h"

#include "sqlite3.h"

SQLite_Error::SQLite_Error(int errorCode, string addMsg)
{
	this->errorCode = errorCode;
	this->errorMessage = sqlite3_errstr(errorCode);
	this->errorMessage += "\n";
	this->errorMessage += addMsg;
}

SQLite_Error::SQLite_Error(sqlite3* database, string addMsg)
	: SQLite_Error(sqlite3_errcode(database), addMsg)
{
}

SQLite_Error::~SQLite_Error()
{
}

void SQLite_Error::checkError(int errorCode, string addMsg) {
	SQLite_Error error(errorCode, addMsg);
	if (error.isError()) {
		throw error;
	}
}

void SQLite_Error::checkError(sqlite3* database, string addMsg) {
	checkError(sqlite3_errcode(database), addMsg);
}

bool SQLite_Error::isError() {
	return (this->errorCode != SQLITE_OK);
}

string SQLite_Error::getErrorMessage() {
	return this->errorMessage;
}

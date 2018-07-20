#include "stdafx.h"
#include "sqlite3.h"
#include <iostream>
#include <string>
#include "database.h"

using namespace std;
database::database() {

	rc = sqlite3_open("C:\\SqlLite3\\CMSDatabase.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}
}
int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}
	printf("\n");
	return 0;
}

void database::databaseclose()
{
	sqlite3_close(db);
}

void database::insertJ48Result(int s, string decision)
{
	string c = "'";
	string a = ",";
	string sq = "insert into J48PResult values("+to_string(s)+a+c+decision+c+ ");";
	sql = (char *)sq.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		
	}
}
void database::insertSVMResult(int s, double result, string decision)
{
	string c = "'";
	string a = ",";
	string sq = "insert into SVMPResult values(" + to_string(s) + a +to_string(result)+a+ c + decision + c + ");";
	sql = (char *)sq.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		
	}
}
void database::insertNNResult(int s, double success,double fail, string decision)
{
	string c = "'";
	string a = ",";
	string sq = "insert into NNPResult values(" + to_string(s)+ a + to_string(success) + a + to_string(fail) + a + c + decision + c + ");";
	sql = (char *)sq.c_str();
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		
	}
}

#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;
class database {
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	char *sql;
	const char* data = "Callback function called";
	int j;

public:
	database();
	void insertJ48Result(int s, string decision);
	void insertSVMResult(int s, double result, string decision);
	void insertNNResult(int s,  double success, double fail, string decision);
	void databaseclose();

};
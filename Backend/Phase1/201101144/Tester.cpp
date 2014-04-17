#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "DBSystem.h"

using namespace std;

int main() {
	int input[] = {0,1,2,1,2,2,3,41,9,39,28,1,30,38,39,31,-1, 42,28};
	int size = 19;

	vector<string> vec;
	FILE *f;
	f = fopen("./countries.csv", "r");
	char *line = NULL;
	int read;
	unsigned long int len = 0;
	while ((read = getline(&line, &len, f)) != -1) {
		line[read-1] = '\0';
		vec.push_back(line);
	}

	DBSystem *dbs = new DBSystem();
	dbs->readConfig("./config.txt");
	dbs->populateDBInfo();
	int i=0;
	for(i=0;i<size;i++) {
		if(input[i] !=-1) {
			string op = dbs->getRecord("countries",input[i]);
			if(vec.at(input[i]).compare(op)==0){

			} else {
				cout<<"Failure for record number "<<input[i]<<" expected = "<<vec.at(input[i])<<" actual= "<<op<<endl;
				exit(-1);
			}
		}
		else
			dbs->insertRecord("countries", "record");
	}
	return 0;
}

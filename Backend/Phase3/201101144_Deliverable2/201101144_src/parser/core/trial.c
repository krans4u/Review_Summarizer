/*	Karan Dhamele	    */
#include<stdio.h>
#include<string.h>
#include "gsp_sqlparser.h"


int main()
{
	gsp_sqlparser *p;
	int rc=gsp_parser_create(dbvoracle,&p);
	if(rc)
		printf("create parser error\n");
	char *sql = 
		"SELECT last_name \n"
		"FROM   employees \n"
		"WHERE  job_id = (SELECT job_id \n"
		"                 FROM   employees \n"
		"                 WHERE  employee_id = 141) \n"
		"       AND salary > (SELECT salary \n"
		"                     FROM   employees \n"
		"                     WHERE  employee_id = 141);\n"
		;

	printf("%s",sql);
	rc = gsp_check_syntax(p,sql);
	if(rc!=0)
		printf("parser error: %s\n",gsp_errmsg(p));
	
}


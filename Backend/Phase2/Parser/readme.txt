version C 0.2.4 (2013-07-13)
* add an extension module to support modify sql feature.
* add new demo: antiSQLInjection, illustrates how to detect sql injection 
	by using general sql parser library.
* add new demo: oracleJoinConverter, illustrate how to Rewrite Oracle 
	proprietary joins to ANSI SQL compliant joins.
* add new demo: gettablecolumns, this demo illustrates how to get all table 
	and column in a sql query.

version C 0.2.4 (2013-06-26)
* add new expression type eet_outer_join for Oracle proprietary join syntax (+)

General SQL Parser C version 0.1.2 (2013-03-14)
* syntax check support: Oracle, DB2, MySQL, SQL Server, PostgreSQL, Teradata, Informix, Sybase, Netezza and MDX.
* [DB2] full parse tree nodes available.
* 32 and 64 bit library available under windows and linux


General SQL Parser C version 0.0.6(static 32 bit on windows/linux)

this version fully support Oracle SQL dialect including PL/SQL.


Features:
1. syntax check
2. fully access to SQL query parse tree
3. traverse of expression
4. parse tree nodes iterator and visitor

Directory:
 core/
 	header files for sql parser core
 demos/
 	demos illustrate how to use SQL library
 ext/
 	extension of sql parser core, with source code included
 lib/
 	static library file including gsp core and collection inside ext/collection


how to build demo using microsoft visual studio
1. open a dos command, enter into demos directory
2. modify env.bat to set correct path while microsoft visual studio was installed
3. nmake -f Makefile.win , all demos execute file will be created under demos/build directory

how to build demo using gcc
1. open a shell, enter into demos directory
2. make -f Makefile.linux , all demos execute file will be created under demos/build directory

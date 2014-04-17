/*	Karan Dhamele	    */
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<stack>
#include<queue>
#include<map>
#include<set>

using namespace std;



#define INF		1000000007LL
#define LL		long long int
#define SI(n)		scanf("%lld",&n);
#define SC(c)		scanf("%c",&c);
#define SS(s)		scanf("%s",s);
#define FOR(x,a,b)	for(LL x=a;x<b;x++)
#define REP(i,n)	for(LL i=0;i<n;i++)
#define MP		make_pair
#define PB		push_back


/* Container's */

#define	VI		vector<LL>
#define PLL             pair<LL,LL>  /* A Single Pair  */
#define VP		vector<PLL> /* Vector of Pairs */
#define VS		vector<string>
#define VVI		vector<VI>
#define VVS		vector<VS>

template<class T>inline T GCD(T a,T b){return b?GCD(b,a%b):a;}
template<class T> inline T LCM(T a,T b){if(a<0)return LCM(-a,b);if(b<0)return LCM(a,-b);return a*(b/GCD(a,b));}
template<class T>inline T POW1(T a,T b,T m){long long x=1,y=a;while(b > 0){if(b%2 == 1){x=(x*y);if(x>m) x%=m;}y = (y*y);if(y>m) y%=m;b /= 2;}return x;}
template<class T>inline T INV(T n,T m){return POW1(n,m-2,m);}
template<class T>inline T SUB(T a,T b,T m){return (a%m-b%m+m)%m;}
template<class T>inline T ADD(T a,T b,T m){return (a%m+b%m)%m;}
template<class T>inline T MUL(T a,T b,T m){return (a%m*b%m)%m;}
template<class T>inline T DIV(T a,T b,T m){return (a%m*(INV(b,m))%m)%m;}
bool check_col(VS fcolumns);
VS cols_in_orderby;
map <string, pair<LL, string> > order_map;
map<string,LL> attribute_to_id;
bool valid_query_flag=true;

#include "parser_overhead.h"
#include "create.cpp"
#include "order_by.cpp"
#include "order_it.cpp"
#include "where.cpp"
string inbetween(VS split_query,string a, string b)
{
	string res="";
	LL flg=0;
	REP(i,split_query.size())
	{
		if(split_query[i]==b)
		{
			break;
		}
		else if(flg==1)
			res+=split_query[i];
		if(split_query[i]==a)
			flg=1;
	}
	return res;
}
bool check_tables(VS ftables)
{
	REP(i,ftables.size())
	{
		if(mymap.find(ftables[i])==mymap.end())
		{
			return false;
		}
	}
	return true;
}
bool check_col(VS fcolumns)
{
	if(fcolumns[0]=="*")
	{
		return true;
	}
	REP(i,fcolumns.size())
	{
		LL flg=0;
		TR(mymap,it)
		{
			REP(j,(*it).S.size())
			{
				if((*it).S[j].F==fcolumns[i])
				{
					flg=1;
					break;
				}
			}
			if(flg==1)
				break;
		}
		if(flg==0)
			return false;
	}
	return true;
}
void createCommand(string query)
{
	create(query);
}
void printtags(string head, VS tags)
{
	cout << head << "";
	LL flg=0;
	if(head=="Columns:")
		flg=1;
	if(tags.size()==0)
	{
		cout << "NA\n";
		return;
	}
	if(flg==1 && tags[0]=="*")
	{
		tags.clear();
		tags=star();
	}
	REP(i,tags.size())
	{
	/*	if(flg==1)
		{
			cout << tags[i] << endl;
		}
		if(tags[i].substr(0,9)=="distinct(")
		{
			tags[i]=tags[i].substr(10);
			tags[i]=tags[i].substr(0,tags[i].size()-1);
			fdistinct.push_back(tags[i]);
		
		}*/
		cout << tags[i] <<  " ";
	}
	cout << endl;
}
void selectCommand(string query)
{
	//cout << query << endl;
	VS split_query=split(query," ");
	func(query);
	if(!check_tables(ftables))
	{
		cout << "Query Invalid\n";
		valid_query_flag=false;
		return;
	}
	//check for columns after select 
	if(!check_col(fcolumns))
	{
		cout << "Query Invalid\n";
		valid_query_flag=false;
		return;
	}
	//check for columns after orderby
	if(!check_orderby(forderby))
	{
		cout << "Query Invalid\n";
		valid_query_flag=false;
		return;
	}
	if(!check_groupby(fgroupby))
	{
		cout << "Query Invalid\n";
		valid_query_flag=false;
		return;
	}
	if(fcolumns[0]=="*")
	{
		fcolumns.clear();
		cout << "in star\n";
		REP(i,mymap[ftables[0]].size())
		{
			//cout << "pushed" << mymap[ftables[0]][i].F << endl;
			fcolumns.PB(mymap[ftables[0]][i].F);
		}
	}
	if(fgroupby.size()!=0)
	{
		VS temp = split(fgroupby[0],"HAVING");
		fgroupby[0]=temp[0];
	}
	cout << "Querytype:select\n";
	printtags("Tablename:",ftables);
	printtags("Columns:",fcolumns);
	//cout << fdistinct.size() << endl;
	printtags("Distinct:",fdistinct);
	printtags("Condition:",fconditions);
	printtags("Orderby:",forderby);
	printtags("Groupby:",fgroupby);
	printtags("Having:",fhaving);
}
void queryType(string query)
{
	VS split_query = split(query," ");
	if(split_query[0]=="create" || split_query[0]=="Create" || split_query[0]=="CREATE")
	{
		createCommand(query);
	}
	else if(split_query[0]=="select" || split_query[0]=="Select" || split_query[0]=="SELECT")
	{
		selectCommand(query);
	}
}
int main()
{
	parse();
	string query;
	getline(cin,query);
	queryType(query);
	if(valid_query_flag)
	{
		cout << "compute_where()\n";
		compute_where();	
	}
}

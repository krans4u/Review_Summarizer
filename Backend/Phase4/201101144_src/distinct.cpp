/*	Jayesh Lahori	    */
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
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

/* General Declarations */

#define INF		1000000007
#define LL		long long int
#define SI(n)		scanf("%lld",&n)
#define SC(c)		scanf("%c",&c)
#define FOR(x,a,b)	for(LL x=a;x<b;x++)
#define REP(i,n)	for(LL i=0;i<n;i++)
#define MP		make_pair
#define PB		push_back
#define F		first
#define S		second
#define TR(container,it) for(typeof(container.begin()) it = container.begin();it != container.end(); it++)


/* Container's */

#define	VI		vector<LL>
#define PLL		pair<LL,LL>  /* A Single Pair  */
#define VP		vector<PLL> /* Vector of Pairs */
#define VS		vector<string>
#define VVI		vector<VI>
#define VVS		vector<VS>

map<pair<string,string>,pair<LL,set<string> > > unique_attributes;
int V(string table,string attribute)
{
	// LL x=attribute's to integer mapping in config file
	LL x=1;
	ifstream file("airports.csv");
	file.seekg(0,ifstream::end);
	LL current_length = file.tellg();
	if(unique_attributes[MP(table,attribute)].F==current_length)
		return unique_attributes[MP(table,attribute)].S.size();
	file.close();
	file.seekg(unique_attributes[MP(table,attribute)].F);
	while(file.good())
	{
		string temp=raw_input();
		unique_attributes[MP(table,attribute)].F+=temp.size();
		VS S=split(temp,",");
		temp=S[x];
		unique_attributes[MP(table,attribute)].S.insert(temp);
	}
	return unique_attributes[MP(table,attribute)].S.size();
}
int main()
{
	V("sad","sad");
	//parse();
	return 0;
}
